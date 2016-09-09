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

var zbuf = Buffer.alloc(32, 0)
console.log(hashes.hash256(zbuf).toString('hex'))
// => 2b32db6c2c0a6235fb1397e8225ea85e0f0e6e8c7b126d0016ccbde0e667151e
```

##### Benchmarks

```
$ uname -srmpio
Linux 4.6.6-200.fc23.x86_64 x86_64 x86_64 x86_64 GNU/Linux
$ node -v
v6.4.0
```

Input Buffer 32 bytes:
```
benchmarking ripemd160, input size: 32, iterations: 200000 (lower is better)
--------------------------------------------------
bindings:            0.408360531s
browser:             0.693749984s
node:                0.776919614s
create-hash/browser: 2.767700147s
==================================================
benchmarking sha1, input size: 32, iterations: 200000 (lower is better)
--------------------------------------------------
bindings:            0.454122623s
browser:             0.647107137s
node:                0.722095691s
create-hash/browser: 2.443707434s
==================================================
benchmarking sha256, input size: 32, iterations: 200000 (lower is better)
--------------------------------------------------
bindings:            0.468423725s
browser:             0.838470451s
node:                0.751801651s
create-hash/browser: 2.748510466s
==================================================
benchmarking hash160, input size: 32, iterations: 200000 (lower is better)
--------------------------------------------------
bindings:            0.573706269s
browser:             1.498219644s
node:                1.626828536s
create-hash/browser: 5.667063203s
==================================================
benchmarking hash256, input size: 32, iterations: 200000 (lower is better)
--------------------------------------------------
bindings:            0.629597252s
browser:             1.587958027s
node:                1.514494228s
create-hash/browser: 5.930286501s
==================================================
```

Input Buffer 1MiB:
```
benchmarking ripemd160, input size: 1048576, iterations: 100 (lower is better)
--------------------------------------------------
bindings:            0.790443096s
browser:             3.330007749s
node:                0.815219769s
create-hash/browser: 7.476185024s
==================================================
benchmarking sha1, input size: 1048576, iterations: 100 (lower is better)
--------------------------------------------------
bindings:            0.721906223s
browser:             2.823331193s
node:                0.221182685s
create-hash/browser: 4.348289727s
==================================================
benchmarking sha256, input size: 1048576, iterations: 100 (lower is better)
--------------------------------------------------
bindings:            1.026594283s
browser:             3.668647001s
node:                0.510602034s
create-hash/browser: 4.180483584s
==================================================
benchmarking hash160, input size: 1048576, iterations: 100 (lower is better)
--------------------------------------------------
bindings:            1.025184445s
browser:             3.613451318s
node:                0.487530048s
create-hash/browser: 4.138467963s
==================================================
benchmarking hash256, input size: 1048576, iterations: 100 (lower is better)
--------------------------------------------------
bindings:            1.023377048s
browser:             3.627327489s
node:                0.490601986s
create-hash/browser: 4.171549607s
==================================================
```

## License

MIT
