'use strict'
var K = [
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
]

function gamma0 (x) {
  return (x >>> 7 | x << 25) ^ (x >>> 18 | x << 14) ^ (x >>> 3)
}

function gamma1 (x) {
  return (x >>> 17 | x << 15) ^ (x >>> 19 | x << 13) ^ (x >>> 10)
}

function ch (x, y, z) {
  return z ^ (x & (y ^ z))
}

function ma (x, y, z) {
  return (x & y) | (z & (x | y))
}

function sigma0 (x) {
  return (x >>> 2 | x << 30) ^ (x >>> 13 | x << 19) ^ (x >>> 22 | x << 10)
}

function sigma1 (x) {
  return (x >>> 6 | x << 26) ^ (x >>> 11 | x << 21) ^ (x >>> 25 | x << 7)
}

function update (state, words, block) {
  for (var i = 0; i < 16; ++i) words[i] = block.readInt32BE(i * 4)
  for (; i < 64; ++i) words[i] = (gamma1(words[i - 2]) + words[i - 7] + gamma0(words[i - 15]) + words[i - 16]) | 0

  var a = state.a | 0
  var b = state.b | 0
  var c = state.c | 0
  var d = state.d | 0
  var e = state.e | 0
  var f = state.f | 0
  var g = state.g | 0
  var h = state.h | 0

  for (var j = 0; j < 64; ++j) {
    var T1 = (h + sigma1(e) + ch(e, f, g) + K[j] + words[j]) | 0
    var T2 = (sigma0(a) + ma(a, b, c)) | 0

    h = g
    g = f
    f = e
    e = (d + T1) | 0
    d = c
    c = b
    b = a
    a = (T1 + T2) | 0
  }

  state.a = (a + state.a) | 0
  state.b = (b + state.b) | 0
  state.c = (c + state.c) | 0
  state.d = (d + state.d) | 0
  state.e = (e + state.e) | 0
  state.f = (f + state.f) | 0
  state.g = (g + state.g) | 0
  state.h = (h + state.h) | 0
}

module.exports = function (input) {
  if (!Buffer.isBuffer(input)) throw new TypeError('Expected input as Buffer')

  // init state
  var state = {
    a: 0x6a09e667,
    b: 0xbb67ae85,
    c: 0x3c6ef372,
    d: 0xa54ff53a,
    e: 0x510e527f,
    f: 0x9b05688c,
    g: 0x1f83d9ab,
    h: 0x5be0cd19
  }
  var words = new Array(16)
  var block = new Buffer(64)

  // consume data
  var offset = 0
  for (var length = input.length; offset + 64 <= length; offset += 64) {
    input.copy(block, 0, offset, offset + 64)
    update(state, words, block)
  }
  var blockOffset = length - offset
  if (blockOffset !== 0) input.copy(block, 0, offset)

  // create padding
  block[blockOffset++] = 0x80
  if (blockOffset > 56) {
    block.fill(0, blockOffset)
    update(state, words, block)
    blockOffset = 0
  }

  block.fill(0, blockOffset, 56)
  block.writeUInt32BE((length / 536870912) | 0, 56)
  block.writeUInt32BE(length * 8 % 4294967296, 60)
  update(state, words, block)

  // produce hash
  var output = new Buffer(32)
  output.writeInt32BE(state.a, 0)
  output.writeInt32BE(state.b, 4)
  output.writeInt32BE(state.c, 8)
  output.writeInt32BE(state.d, 12)
  output.writeInt32BE(state.e, 16)
  output.writeInt32BE(state.f, 20)
  output.writeInt32BE(state.g, 24)
  output.writeInt32BE(state.h, 28)
  return output
}
