// app.js
var prompt = require('prompt');
var SerialPort = require('serialport');

var async = require('async');

var serial;

async.series({
      get_serial: function(callback){
        SerialPort.list(function (err, ports) {
              console.log('Selectable serial ports:');
              var k = 1;
              ports.forEach(function(port) {
                console.log('('+k+') '+port.comName); k++;
              });
              prompt.start();

              prompt.get({properties: {port: {required: true, type: 'number', conform: function(value){
                    if (value > 0 && value <= ports.length) return true;
                    else return false;
                }}}}, function (err, result) {
                    if (err) return; //cb(null);
                    choosen_port=  ports[result.port-1].comName;
                    console.log('Choosen port:', ports[result.port-1].comName);

                    //port =  choosen_port;
                    serial = new SerialPort(choosen_port, {
                        parser: SerialPort.parsers.readline('\n'),
                        baudRate: 9600,
                        autoOpen: true // autoOpen flag set to false, manually need to open the port
                    });



                  //  cb(serial);

                  });

        });
       callback(null, 1);

     },

    server: function(callback) {
      require("./server")(function(server){
        var http = server.http;
        var io = server.io;   // socket.io

        require("./api")(http, io); // add the api to the server

        io.on('connection', function(client){
            console.log('Client connected...');

            client.on('join', function(data) {
                console.log(data);
                client.emit('messages', 'Hello from server');
            });

            client.on("command", function(data){
              console.log(data);
              serial.open(function (error) {
                if ( error ) {
                  console.log('failed to open: '+error);
                  throw error;
                } else {
                   console.log('Serial port opened');

                }
              });

              if (serial.isOpen()){
                //serial.write(String(msg), callback);
                serial.write(data);//JSON.stringify({"dst":2, "op":2, "data":1}));
              }else{
                console.log('SerialPort not open!');
            }
              //serial.write(data);
            });
          });

      });

      // app.use(express.static(__dirname + '/node_modules'));
      //
      // app.get('/', function(req, res,next) {
      //     res.sendFile(__dirname + '/index.html');
      // });
      //
      // io.on('connection', function(client){
      //     client = client;
      //     console.log('Client connected...');
      //
      //     client.on('join', function(data) {
      //         console.log(data);
      //         client.emit('messages', 'Hello from server');
      //     });
      //
      // });

    },
},  function(err, results) {
      // results is now equal to: {one: 1, two: 2}

      // debug('Results: ', results);

});
//
// var getSerial = function(cb){
//   SerialPort.list(function (err, ports) {
//         console.log('Selectable serial ports:');
//         var k = 1;
//         ports.forEach(function(port) {
//           console.log('('+k+') '+port.comName); k++;
//         });
//         prompt.start();
//
//         prompt.get({properties: {port: {required: true, type: 'number', conform: function(value){
//               if (value > 0 && value <= ports.length) return true;
//               else return false;
//           }}}}, function (err, result) {
//               if (err) cb(null);
//               choosen_port=  ports[result.port-1].comName;
//               console.log('Choosen port:', ports[result.port-1].comName);
//
//               //port =  choosen_port;
//               serial = new SerialPort(choosen_port, {
//                   parser: SerialPort.parsers.readline('\n'),
//                   baudRate: 9600
//                 //  autoOpen: false // autoOpen flag set to false, manually need to open the port
//               });
//               cb(serial);
//
//             });
//
//   });
// };
//
//
// getSerial( function(serial){
//
//   serial.on("data", function(data){
//     console.log(data);
//   });
//
//
// });


// app.use(express.static(__dirname + '/node_modules'));
//
// app.get('/', function(req, res,next) {
//     res.sendFile(__dirname + '/index.html');
// });
//
// io.on('connection', function(client){
//     client = client;
//     console.log('Client connected...');
//
//     client.on('join', function(data) {
//         console.log(data);
//         client.emit('messages', 'Hello from server');
//     });
//
// });



// console.log("listening on port ");
// server.listen(4200);
