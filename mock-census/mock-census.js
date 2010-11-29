// TODO beef up AHR to allow streamed parsing
"use strict";
(function (undefined) {
  var fs = require('fs'),
    request = require('ahr'),
    stream,
    node = process.argv[0],
    self = process.argv[1],
    fulluri = process.argv[2];

  self = self.substr(self.lastIndexOf('/') + 1);

  require('remedial');

  function usage() {
    console.log("Usage: node {self}".supplant({self: self}) + 
      " file:///path/to/file | http://path/to/file");
  }


  // Head, and Dependent "Classes"
  function Comment(lines) {
    while (true) {
      line = lines.shift();
      if (undefined === line || null === line) {
        throw new Error("Expected 'Dependent' or 'end' but reach end-of-file");
      }
      if (!line.match(/\s*#/)){
        break;
      }
    }
    return line;
  }

  function Dependent(lines) {
    var line, dep;
    line = Comment(lines);
    
    if (line.match(/^Dependent\s*/)) {
      parts = line.split(/\s+/);
      dep = {
        // no error checking in spec
        name: parts[1],
        gender: parts[2],
        age: parts[3],
        height: parseInt(parts[4], 10),
      };
    } else if (line.match(/^End\s*/)) {
      return false;
    } else {
      throw new Error("Expected 'Dependent' or 'End' but saw\n    " + line.substr(0,20));
    }
    return dep;
  }

  function Head(lines) {
    var line, head, parts, dep;
    line = Comment(lines);

    if (line.match(/^Head\s*/)) {
      parts = line.split(/\s+/);
      head = {
        // no error checking in spec
        name: parts[1],
        gender: parts[2],
        eye_color: parts[3],
        hair_color: parts[4],
        height: parseInt(parts[5], 10),
        deps: []
      };
      while (dep = Dependent(lines)) {
        head.deps.push(dep);
      }
    } else if (line.match(/^SUPER-END\s*/)) {
      return false;
    } else {
        throw new Error("Expected 'Head' or 'SUPER-END' but saw\n    " + line.substr(0,20));
    }
    return head;
  }

  function readFile(file) {
    var promise = require('futures').promise(),
      stream,
      data = new Buffer('');

    stream = fs.createReadStream(file, { flags: 'r', encoding: 'utf8' });
    stream.on('error', function (err) {
      promise.fulfill(err, stream, data);
    });
    stream.on('data', function (chunk) {
      data += chunk;
    });
    stream.on('end', function () {
      promise.fulfill(undefined, stream, data);
    });
    return promise;
  }

  // Queries

  // Average height of Heads of Household
  function query1(heads) {
    var heights = 0.0;
    heads.forEach(function (head) {
      heights += head.height;
    });
    console.log("Average Height of Heads of Household: " + (heights / heads.length));
  }

  // What is the height of the tallest of all dependents?
  function query2(heads) {
    var max = 0.0;
    heads.forEach(function (head) {
      head.deps.forEach(function (dep) {
        max = Math.max(max, dep.height);
      });
    });
    console.log("Height of tallest Dependent: " + max);
  }

  // The height of the shortest Dependent of a female Head of Household
  function query3(heads) {
    var min = Infinity;
    heads.forEach(function (head) {
      if ('F' !== head.gender) {
        return;
      }
      head.deps.forEach(function (dep) {
        min = Math.min(min, dep.height);
      });
    });
    console.log("Height of shortest Dependent of a Female-Headed Household: " + min);
  }

  // Average height of male dependents of brown-haired male heads of houshold
  function query4(heads) {
    var heights = 0.0, count = 0;
    heads.forEach(function (head) {
      if ('m' !== head.gender && 'brown' !== head.hair_color) {
        return;
      }
      head.deps.forEach(function (dep) {
        count += 1;
        heights += dep.height;
      });
    });
    console.log("Average height of male dependent of brown-haired male Heads of Household: " + (heights / count));
  }

  function parseChunk(chunk) {
    /*
    // TODO be more memory efficient
    // by seeking into the buffer
    data += chunk
    while (true) {
      index = data.indexOf('\n')
      if (-1 === index) {
        break;
      }
      line = data.substr(0, index);
      data = data.substr(index + 1);
      parseLine(line);
    }
    */
  }

  var data = '';
  function parseData(err, x, chunk, end) {
    if (!end) {
      data += chunk.toString();
      return;
    }
    var lines = data.split('\n'),
      heads = [],
      curHead;

    while (curHead = Head(lines)) {
      heads.push(curHead);
    }
    console.log(JSON.stringify(heads, null, '  '));
    query1(heads);
    query2(heads);
    query3(heads);
    query4(heads);
    return heads;
  }

  function main() {
    if (!fulluri) {
      usage();
      return;
    }
      
    request.get(fulluri, undefined, { stream: true}).when(parseData);

    //if ('file' !== uri.protocol && '' === uri.protocol || uri.protocol.match(/^http[s]?:$/)) {
    //  request.get(fulluri, undefined, { stream: true}).when(parseData);
    //} else {
    //  usage();
    //  return;
    //}
  }

  main();

}());
