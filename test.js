'use strict';

var crypto = require('crypto');
var supersha = require('./');
var assert = require('assert');

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

assert.strictEqual(
  hash256(b).toString('hex'),
  supersha.hash256(b).toString('hex'));

assert.strictEqual(
  sha256(b).toString('hex'),
  supersha.sha256(b).toString('hex'));

assert.strictEqual(
  sha256hmac(b, k).toString('hex'),
  supersha.sha256hmac(b, k).toString('hex'));

assert.throws(function() {
  supersha.sha256(1);
});

assert.throws(function() {
  supersha.hash256(1);
});

assert.throws(function() {
  supersha.sha256hmac(1);
});

assert.throws(function() {
  supersha.sha256hmac(new Buffer(1), 1);
});

assert.throws(function() {
  supersha.sha256();
});

assert.throws(function() {
  supersha.hash256();
});

assert.throws(function() {
  supersha.sha256hmac();
});

assert.throws(function() {
  supersha.sha256hmac();
});
