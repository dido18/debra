var express = require('express');

module.exports = function(http, io){

  http.use(express.static(__dirname + '/node_modules'));

  http.get('/', function(req, res,next) {
      res.sendFile(__dirname + '/index.html');
  });
};
