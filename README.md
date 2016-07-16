# supersha

SHA256 exposed to node.js from Pieter Wuille's [libsecp256k1][secp]. Used in
[bcoin][bcoin].

## Usage

``` js
var supersha = require('supersha');
var data = new Buffer('01020304', 'hex');
var key = new Buffer('05060708', 'hex');

var hash1 = supersha.sha256(data);

var hash2 = supersha.sha256hmac(data, key);

var hash3 = supersha.hash256(data);

console.log('sha256: %s', hash1.toString('hex'));
console.log('sha256 hmac: %s', hash2.toString('hex'));
console.log('double sha256: %s', hash3.toString('hex'));
```

Outputs:

```
sha256: 9f64a747e1b97f131fabb6b447296c9b6f0201e79fb3c5356e6c77e89b6a806a
sha256 hmac: 791ff56c5d7624c816777b13d0621b51f144853a371170e13644d63a77b2596f
double sha256: 8de472e2399610baaa7f84840547cd409434e31f5d3bd71e4d947f283874f9c0
```

## Benchmarks

``` bash
$ node bench.js
crypto.sha256: ops=100000, time=0.555176535, rate=180122.88650
supersha.sha256: ops=100000, time=0.407243698, rate=245553.21664
crypto.hash256: ops=100000, time=0.968488985, rate=103253.62658
supersha.hash256: ops=100000, time=0.482557892, rate=207229.02196
crypto.sha256hmac: ops=100000, time=0.781748435, rate=127918.38848
supersha.sha256hmac: ops=100000, time=0.539863217, rate=185232.10482
```

## License

Copyright (c) 2016, Christopher Jeffrey. (MIT License)

See LICENSE for more info.

[secp]: https://github.com/bitcoin-core/secp256k1
[bcoin]: https://github.com/bcoin-org/bcoin
