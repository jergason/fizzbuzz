#!/usr/bin/env node
"use strict";
var sys = require('sys');
(function () {
  var i, msg;
  for (i = 1; i <= 100; i += 1) {
    msg = '';

    if (0 === (i % 3)) { msg += "Fizz"; }
    if (0 === (i % 5)) { msg += "Buzz"; }
    if (msg.length > 0) { console.log(msg); }
  }
}());
