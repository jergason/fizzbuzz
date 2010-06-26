#!/usr/bin/env node
"use strict";
var sys = require('sys');
(function () {
  var i, n;
  for (i = 1; i <= 100; i += 1) {
    n = false;

    if (0 === (i % 3)) {
      n = true;
      sys.print("Fizz");
    }
    if (0 === (i % 5)) {
      n = true;
      sys.print("Buzz");
    }
    if (true === n) {
      sys.print("\n");
    }
  }
}());
