#!/usr/bin/env node

var serialport = require('serialport');
var path = require('path');
var argv = require('./components/argv_parser.js');
var config = require('./config.json');   // configuration file
var Datastore = require('nedb');    // database
var async = require('async');


// if defined use CLI debug (NB. current choice is not stored inside the config.json file, so other scripts that are including the file from the disk and are not using this variable istance may not retrieve the right DEBUG choice from the User)
if (typeof argv.debug !== 'undefined') config.debug = argv.debug; // if defined use CLI debug (NB. current choice is not stored inside the config.json file, so other scripts that are including the file from the disk and are not using this variable istance may not retrieve the right DEBUG choice from the User)
var debug = require('./components/debug.js')();

var db = new Datastore();
var db = {};

// Radio Frequency Class platform-independent
var RadioHead433Mhz;


// var users = new Datastore({ filename: 'users.db', autoload: true });
// var tweets = new Datastore({ filename: 'tweets.db', autoload: true });
// var messages = new Datastore({ filename: 'messages.db', autoload: true });


// Starting Flow
async.series({
        init_db: function(callback){
             debug('calling init_db');

            db.BEES_CARDS = new Datastore({
                filename: path.resolve(__dirname, './DB/bees.db'),
                autoload: true
            });

            // Compact DB at regular intervals (see nedb: #Persistence)
            if (config.db_compact_interval > 0){
                db.BEES_CARDS.persistence.setAutocompactionInterval(config.db_compact_interval * 60000 * 60);
            }

            dbFunctions = require('./components/dbFunctions.js')(db, config);
            callback(null, 1);
        },
        init_webhooks: function(callback){
            debug('calling init_webhooks');
            // Initialize WebHooks module.
            var WebHooks = require('node-webhooks');
            webHooks = new WebHooks({
                db: path.resolve(__dirname, './DB/webHooksDB.json') // json file that store webhook URLs
            });
            notification = require('./components/notification.js')(dbFunctions, webHooks);
            callback(null, 1);
        },
        platform: function(callback) {
            debug('platform configuration');
            require('./components/arduino-platform.js')(argv, function(rf) {
                RadioHead433Mhz = rf; // platform independent class
                callback(null, RadioHead433Mhz);

            });

        },
        load_db: function(callback) {
            // Put default demo cards if CARDS DB is empty
            dbFunctions.initDBCards(require('./components/demo_cards.json')).then(dbFunctions.initDBSettings).then(function(settings) {
                callback(null, 1);
            }).catch(function(err) {
                console.log('load_db error:', err);
                console.log(err.stack);
            });
        },
        init_rf: function(callback) {
            // Listen on Arduino Serial Port
            RadioHead433Mhz.openSerialPort(function() {
                setTimeout(function() {
                    callback(null, 1);
                }, 2000); // Arduino AutoReset requires to wait a few seconds before sending data!
            });

        },
        server: function(callback) {
            // Starting HTTP Server, API, and Web Socket
            require('./components/server.js')(argv, function(server) {
                // server contains the html and socket.io object
                // Handling routes and Web Socket Handler.
                var http = server.http;
                var io = server.io;   // socket.io

                require('./components/api.js')(http, io, RadioHead433Mhz, dbFunctions, webHooks);

                // Web Socket handler
                require('console-mirroring')(io); // Console mirroring

                var socketFunctions = require('./components/socketFunctions.js')(io, RadioHead433Mhz, dbFunctions);

                /* LISTENERS */
                io.on('connection', socketFunctions.onConnection);

                db.BEES_CARDS.on('inserted', function(card) { // card just inserted
                    // refresh every client UI
                    socketFunctions.asyncEmitInitCards();

                });

                db.BEES_CARDS.on('removed', function(card) { // a card was removed
                    // remove from DB codes attached to this card:
                    var codes_to_remove = {};
                    if (card.type === 'switch') codes_to_remove = {
                        $or: [{
                            code: card.device.on_code
                        }, {
                            code: card.device.off_code
                        }]
                    };
                    else if (card.type === 'alarm') codes_to_remove = {
                        code: card.device.trigger_code
                    };
                    else if(card.type === 'monitor') codes_to_remove = {
                        code : card.device.monitor_code
                    };
                    else codes_to_remove = undefined;

                    if (codes_to_remove) {
                        // delete codes.
                        db.RFCODES.remove(codes_to_remove, {
                            multi: true
                        }, function(err, numRemoved) {
                            if (err) console.log(err);
                            console.log(numRemoved + ' code/s deleted.');
                        });
                    }

                    // delete img file
                    if (card.img) fs.unlink(path.resolve('./www/', card.img), function(err){ if (err) console.error('DeleteFile: file not found', err.path); });

                    console.log('Card ' + card.shortname + ' deleted.');
                    // refresh every client UI
                    socketFunctions.asyncEmitInitCards();

                });

                RadioHead433Mhz.on(function(msgFromArduino) {
                    //console.log(msgFromArduino);
                    debug('Message received: ', msgFromArduino);
                    // dbFunctions.getAllBeeCards().then(function(docs){
                    //     console.log(docs)
                    // });
                    console.log(msgFromArduino);

                    var msg  = {
                       dst: 2,
                       op: 2,
                       data:1
                   };
                 // {"dst": 2, "op": 2 , "data":1 } // accende i led ler del'ape 2
                 // {"dst": 2, "op": 2 , "data":0 } // spegne i led ler del'ape 2

                    RadioHead433Mhz.sendMsg(JSON.stringify(msg),function(){
                      console.log("Sent to beeheve");
                    });

                    //
                    // if (msgFromArduino.status === 'received'){
                    //   dbFunctions.isBeeRegistered(msgFromArduino).then(function(isRegistered){
                    //     if (isRegistered)
                    //       console.log(isRegistered);
                    //     else{
                    //       console.log("does not exit");
                    //       dbFunctions.putBeeCard(msgFromArduino).then(function(result){
                    //           console.log("inserted");
                    //       });
                    //     }
                    //   });

                    // }
                    // if (msgFromArduino.status === 'received') {
                    //     dbFunctions.putCodeInDB(msgFromArduino).then(function(mex) {
                    //               debug(mex);
                    //               dbFunctions.isCodeAvailable(msgFromArduino.code).then(function(result) { // a code is available if not ignored and not assigned.
                    //                   debug('code available: '+result.isAvailable+' assigned to: '+result.assignedTo);
                    //
                    //                   if (result.isAvailable)
                    //                       io.emit('newRFCode', msgFromArduino); // sent to every open socket.
                    //                   else{
                    //                       // code not available, check if the code is assigned to an alarm card
                    //
                    //                       if (msgFromArduino.type === "monitor"){
                    //                         var card_shortname = result.assignedTo;
                    //                          dbFunctions.addMonitorValue(card_shortname, msgFromArduino.value).then(function(card){
                    //                              debug('Value: '+msgFromArduino.value+' added to card: '+result.assignedTo);
                    //                              io.emit('newMonitorValue', card);
                    //                          }, function(err){
                    //                            console.error(err);
                    //                          });
                    //
                    //                       }else if (msgFromArduino.type === "switch"){
                    //                         var card_shortname = result.assignedTo;
                    //
                    //                         dbFunctions.alarmTriggered(card_shortname, 'alarm').then(function(card){
                    //                                 if (card){
                    //                                    io.emit('uiTriggerAlarm', card);
                    //                                    // if Alarm is armed send email or other kind of notification (Telegram mex).
                    //                                    if (card.device.armed){
                    //                                         notification.alarmAdviseAll(card);
                    //                                     }
                    //
                    //                                 }
                    //                         }, function(err){ console.error(err);});
                    //                    }
                    //                   }
                    //                   // another WebHook call type (code detected)
                    //                   notification.webHookCodeDetected(msgFromArduino);
                    //               }).catch(function(err) {
                    //                   console.error(err);
                    //               });
                    //
                    //           }, function(err) {
                    //               console.error(err);
                    //           });
                    //
                    //       }

                });


            });

            callback(null, 1);
        }

    },
    function(err, results) {
        // results is now equal to: {one: 1, two: 2}

        // debug('Results: ', results);

});


// (Ctrl + C) - Handler
if (process.platform === 'win32') {
    var rl = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout
    });

    rl.on('SIGINT', function() {
        process.emit('SIGINT');
    });

    rl.close(); // without it we have conflict with the Prompt Module.
}

process.on('SIGINT', function() {
    console.log('Closing...');
    if (typeof rf433mhz !== 'undefined') { // Close Serial Port
        rf433mhz.close(function(err) {
            if (err) console.error('Error: ', err);
            else console.log('Serial Port closed.');
            //graceful shutdown
            process.exit();
        });

    } else process.exit();

});
