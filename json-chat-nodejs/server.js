(function () {
  "use strict";

  var connect = require('connect')
    , server
    ;

  server = connect.createServer(
      connect.favicon()
    , connect.static(__dirname + '/public')
    // implement chat storage engine
  );

  module.exports = server;
}());
