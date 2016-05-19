'use strict'
function rotl1 (num) {
  return (num << 1) | (num >>> 31)
}

function rotl5 (num) {
  return (num << 5) | (num >>> 27)
}

function rotl30 (num) {
  return (num << 30) | (num >>> 2)
}

function fn0 (b, c, d) {
  return (b & c) | ((~b) & d)
}

function fn1 (b, c, d) {
  return b ^ c ^ d
}

function fn2 (b, c, d) {
  return (b & c) | (b & d) | (c & d)
}

function update (state, words, block) {
  for (var i = 0; i < 16; ++i) words[i] = block.readInt32BE(i * 4)
  for (; i < 80; ++i) words[i] = rotl1(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16])

  var a = state.a | 0
  var b = state.b | 0
  var c = state.c | 0
  var d = state.d | 0
  var e = state.e | 0

  for (i = 0; i < 80; ++i) {
    var t
    if (i < 20) {
      t = (e + fn0(b, c, d) + rotl5(a) + words[i] + 0x5a827999) | 0
    } else if (i < 40) {
      t = (e + fn1(b, c, d) + rotl5(a) + words[i] + 0x6ed9eba1) | 0
    } else if (i < 60) {
      t = (e + fn2(b, c, d) + rotl5(a) + words[i] + 0x8f1bbcdc) | 0
    } else { // i < 80
      t = (e + fn1(b, c, d) + rotl5(a) + words[i] + 0xca62c1d6) | 0
    }

    e = d
    d = c
    c = rotl30(b)
    b = a
    a = t
  }

  state.a = (a + state.a) | 0
  state.b = (b + state.b) | 0
  state.c = (c + state.c) | 0
  state.d = (d + state.d) | 0
  state.e = (e + state.e) | 0
}

module.exports = function (input) {
  if (!Buffer.isBuffer(input)) throw new TypeError('Expected input as Buffer')

  // init state
  var state = {
    a: 0x67452301,
    b: 0xefcdab89,
    c: 0x98badcfe,
    d: 0x10325476,
    e: 0xc3d2e1f0
  }
  var words = new Array(80)
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
  var output = new Buffer(20)
  output.writeInt32BE(state.a, 0)
  output.writeInt32BE(state.b, 4)
  output.writeInt32BE(state.c, 8)
  output.writeInt32BE(state.d, 12)
  output.writeInt32BE(state.e, 16)
  return output
}
