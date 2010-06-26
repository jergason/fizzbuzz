#!/usr/bin/env node
"use strict";
var sys = require('sys');
(function () {
  var seq = [];
  function fibonacci(a, b) {
    seq.push(a);
    if (a >= 100) {
      seq.push(b);
      return;
    }
    fibonacci(b, a+b);
  }
  fibonacci(0,1);
  sys.print(seq.join(', ') + "\n");
}());
