# bitcoinjs-hash

[![NPM Package](https://img.shields.io/npm/v/bitcoinjs-hash.svg?style=flat-square)](https://www.npmjs.org/package/bitcoinjs-hash)
[![Build Status](https://img.shields.io/travis/bitcoinjs/bitcoinjs-hash.svg?branch=master&style=flat-square)](https://travis-ci.org/bitcoinjs/bitcoinjs-hash)
[![Dependency status](https://img.shields.io/david/bitcoinjs/bitcoinjs-hash.svg?style=flat-square)](https://david-dm.org/bitcoinjs/bitcoinjs-hash#info=dependencies)

[![js-standard-style](https://cdn.rawgit.com/feross/standard/master/badge.svg)](https://github.com/feross/standard)

Experimental package with hashes for bitcoin.

##### Example

```js
var hashes = require('bitcoinjs-hash')
var bindings = require('bitcoinjs-hash/bindings')
var browser = require('bitcoinjs-hash/browser')
var node = require('bitcoinjs-hash/node')

var zbuf = new Buffer(32).fill(0)
console.log(hashes.hash256(zbuf).toString('hex'))
// => 2b32db6c2c0a6235fb1397e8225ea85e0f0e6e8c7b126d0016ccbde0e667151e
```

##### Benchmarks

Input Buffer 32 bytes:

```
benchmarking ripemd160, input size: 32 (lower is better)
--------------------------------------------------
bindings: 1892720281
browser:  3687225123
node:     4086482603
==================================================
benchmarking sha1, input size: 32 (lower is better)
--------------------------------------------------
bindings: 2226064342
browser:  4196960073
node:     4467493046
==================================================
benchmarking sha256, input size: 32 (lower is better)
--------------------------------------------------
bindings: 2432184606
browser:  4501880713
node:     4147082863
==================================================
benchmarking hash160, input size: 32 (lower is better)
--------------------------------------------------
bindings: 3008683757
browser:  8262049017
node:     8644102730
==================================================
benchmarking hash256, input size: 32 (lower is better)
--------------------------------------------------
bindings: 3156226659
browser:  8753243682
node:     8188902514
==================================================
```

Input Buffer 1 megabyte:

```
benchmarking ripemd160, input size: 1048576 (lower is better)
--------------------------------------------------
bindings: 805671255
browser:  4600740963
node:     844800495
==================================================
benchmarking sha1, input size: 1048576 (lower is better)
--------------------------------------------------
bindings: 755236435
browser:  3030592863
node:     234563606
==================================================
benchmarking sha256, input size: 1048576 (lower is better)
--------------------------------------------------
bindings: 1079667428
browser:  3824689848
node:     508562052
==================================================
benchmarking hash160, input size: 1048576 (lower is better)
--------------------------------------------------
bindings: 1065501642
browser:  3747935491
node:     509691499
==================================================
benchmarking hash256, input size: 1048576 (lower is better)
--------------------------------------------------
bindings: 1082729955
browser:  3795854074
node:     508967488
==================================================
```

## License

MIT
