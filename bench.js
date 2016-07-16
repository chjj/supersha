'use strict';

var crypto = require('crypto');
var supersha = require('./');

function bench(name) {
  var start = process.hrtime();
  return function end(ops) {
    var elapsed = process.hrtime(start);
    var time = elapsed[0] + elapsed[1] / 1e9;
    var rate = ops / time;

    console.log('%s: ops=%d, time=%d, rate=%s',
      name, ops, time, rate.toFixed(5));
  };
}

function sha256(data) {
  return crypto.createHash('sha256').update(data).digest();
}

function hash256(data) {
  return sha256(sha256(data));
}

function sha256hmac(data, salt) {
  var hmac = crypto.createHmac('sha256', salt);
  return hmac.update(data).digest();
}

var b = new Buffer(400);

for (var i = 0; i < b.length; i++)
  b[i] = i & 0xff;

var k = new Buffer(40);

for (var i = 0; i < k.length; i++)
  k[i] = i & 0xff;

var end = bench('crypto.sha256');
for (var i = 0; i < 100000; i++) {
  sha256(b);
}
end(i);

var end = bench('supersha.sha256');
var start = Date.now();
for (var i = 0; i < 100000; i++) {
  supersha.sha256(b);
}
end(i);

var end = bench('crypto.hash256');
for (var i = 0; i < 100000; i++) {
  hash256(b);
}
end(i);

var end = bench('supersha.hash256');
var start = Date.now();
for (var i = 0; i < 100000; i++) {
  supersha.hash256(b);
}
end(i);

var end = bench('crypto.sha256hmac');
for (var i = 0; i < 100000; i++) {
  sha256hmac(b, k);
}
end(i);

var end = bench('supersha.sha256hmac');
var start = Date.now();
for (var i = 0; i < 100000; i++) {
  supersha.sha256hmac(b, k);
}
end(i);
