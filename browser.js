'use strict'
var ripemd160 = require('./lib/ripemd160')
var sha1 = require('./lib/sha1')
var sha256 = require('./lib/sha256')

exports.ripemd160 = ripemd160
exports.sha1 = sha1
exports.sha256 = sha256

exports.hash160 = function (input) { return ripemd160(sha256(input)) }
exports.hash256 = function (input) { return sha256(sha256(input)) }
