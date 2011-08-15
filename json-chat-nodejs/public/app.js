(function () {
  "use strict";

  var $ = require('ender')
    , request = require('ahr2')
    ;

  function assignHandlers() {
    // do long-polling to get new chat messages
    function getNewMessages() {

      request({
          "method": "GET"
        , "href": "/RoomA"
        , "query": {
              since: new Date().valueOf() - (10 * 1000)
            , ignoreme: 'foo'
          }
      }).when(function (err, ahr, data) {
        console.log('should implement a GET request here');
        setTimeout(getNewMessages, 10 * 1000);
      });
    }
    getNewMessages();

    // Assign the event handler on the form
    $('body').delegate('#chatform form', 'submit', function (ev) {
      ev.preventDefault();

      request({
          "method": "POST"
        , "href": "/RoomA"
        , "body": {
              name: $("#chatform [name=name]").val()
            , message: $("#chatform [name=message]").val()
          }
        , "headers": { "Content-Type": "application/json" }
      }).when(function (err, ahr, data) {
        alert('you clicked the submit button (or perhaps hit enter)');
        console.log(err, ahr, data);
      });
    });
  }

  // wait until the dom is ready to do stuff with it
  $.domReady(assignHandlers);
}());
