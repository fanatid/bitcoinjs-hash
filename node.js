'use strict'
var createHash = require('crypto').createHash

function ripemd160 (input) {
  if (!Buffer.isBuffer(input)) throw new TypeError('Expected input as Buffer')
  return createHash('ripemd160').update(input).digest()
}

function sha1 (input) {
  if (!Buffer.isBuffer(input)) throw new TypeError('Expected input as Buffer')
  return createHash('sha1').update(input).digest()
}

function sha256 (input) {
  if (!Buffer.isBuffer(input)) throw new TypeError('Expected input as Buffer')
  return createHash('sha256').update(input).digest()
}

exports.ripemd160 = ripemd160
exports.sha1 = sha1
exports.sha256 = sha256

exports.hash160 = function (input) { return ripemd160(sha256(input)) }
exports.hash256 = function (input) { return sha256(sha256(input)) }
