
var express = require('express');
var path = require('path');
var fs = require('fs');
var version = require('../package.json').version;
var debug = require('./debug.js')();
var validator = require('validator');
var multer  = require('multer');

var upload = multer({ dest: path.resolve(__dirname,'../www/uploads/'),
	fileFilter: function(req, file, cb){ // file filter operations
		var allowed_img_ext = ['.jpg','.jpeg','.png','.gif','.bmp'];
		//debug(file);
		if (file) // img file not mandatory
			if (validator.isIn(path.extname(file.originalname).toLowerCase(), allowed_img_ext)) cb(null, true);
				else cb(null, false);
	} });

// loading backgrounds imgs
// var BACKGROUNDS = fs.readdirSync(path.join(__dirname, '../www/assets/img/backgrounds'));
//debug('Available UI backgrounds:', BACKGROUNDS);

module.exports = function(app, io, RadioHead433Mhz, dbFunctions, webHooks){

	// get settings
	app.route('/api/settings/get').get(function(req, res){
		dbFunctions.getDBSettings().then(function(docs){
			res.status(200).json({status: 'ok', settings: docs});
		}).catch(function(err){
			res.status(400).json({status: 'error', error: err.toString()});
		});
	});

	// return all the codes in DB
	app.route('/api/bees/all').get(function (req, res){
		dbFunctions.getAllCards().then(function(codes){
			res.status(200).json(codes);
		}, function(err){
			res.status(400).json({status: 'error', error: err.toString()});
		});
	});

	// new card insertion
	app.post('/api/bees/new', upload.single('card_img'), function (req, res, next) {
			// req.body will hold the text fields, if there were any

			if (checkRequiredParams(req.body)){
				dbFunctions.checkDatabaseCorrispondence(req.body).then(function(){
					// req.body will hold the img file
					if (req.file){
						var file_name = req.body.shortname.trim().toLowerCase().replace(new RegExp(' ', 'g'), '-')+path.extname(req.file.originalname);
						var origin_path = path.resolve(__dirname, '..', req.file.path);
						var destination_path = path.resolve(__dirname, '../www/uploads/', file_name);
						fs.rename(origin_path, destination_path, function (err) { // rename file uploaded
							if (err) return res.status(400).json({done: false, err: err.toString()});
							// put data in DB
							dbFunctions.putCardInDatabase(req, './uploads/'+file_name).then(function(newCard){
								res.status(200).json({done: true, newCard: newCard});
							}).catch(function(err){
								res.status(400).json({done: false, err: err.toString()});
							});
						});
					}else{
						// put data (no img) in DB
						dbFunctions.putCardInDatabase(req).then(function(newCard){
								res.status(200).json({done: true, newCard: newCard});
							}).catch(function(err){
								res.status(400).json({done: false, err: err.toString()});
							});

					}
				}).catch(function(err){
					res.status(400).json({done: false, err: err});
				});
			}else res.status(400).json({done: false, err: 'Make sure to pass all the required params.'});

	});
};
function checkRequiredParams(params){ // required params (headline, shortname, room, type, on_code/off_code)

  	debug('API:/api/bees/new - Received parameters (monitor_code?): ', params);

  	if (typeof params === 'undefined') return false;

  	var required_params = ['headline', 'shortname', 'room', 'type'];
  	var params_name = Object.keys(params);

  	var keepGoing = true;
  	required_params.forEach(function(param){
  		if (!validator.isIn(param, params_name)) keepGoing = false;
  	});
  	if (!keepGoing) return false;

  	// check background color (must be an hex color if passed)
  	if (params.background_color && !validator.isHexColor(params.background_color)) return false;

  	// check for type-specific params
  	switch (params.type){
  		case 'switch':
  			if (validator.isInt(params.on_code) &&
  				validator.isInt(params.off_code)) return true;
  			else return false;
  		break;
  		case 'alarm':
  			if (validator.isInt(params.trigger_code)) return true;
  			else return false;
  		break;
  		case 'info':
  			// no specific params needed
  			return true;
  		break;
  		case 'monitor':
  			// TODO in feature release. Used by temperature sensor etc.
  			if (validator.isInt(params.monitor_code)) return true;
  			return true;
  		break;
  	}

  }
