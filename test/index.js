'use strict'
var test = require('tape')
var vectors = require('hash-test-vectors')

function runTests (hashes) {
  Object.keys(hashes).forEach(function (key) {
    if (key === 'path') return
    test(key + ' should throw TypeError if input is not Buffer', function (t) {
      t.throws(function () {
        hashes[key](null)
      }, /^TypeError: Expected input as Buffer$/)
      t.end()
    })
  })

  vectors.forEach(function (vector, i) {
    var input = new Buffer(vector.input, 'base64')

    var algs = ['ripemd160', 'sha1', 'sha256']
    algs.forEach(function (alg) {
      test(alg + '#' + i, function (t) {
        t.same(hashes[alg](input).toString('hex'), vector[alg])
        t.end()
      })
    })

    test('hash160#' + i, function (t) {
      t.same(hashes.hash160(input), hashes.ripemd160(hashes.sha256(input)))
      t.end()
    })

    test('hash256#' + i, function (t) {
      t.same(hashes.hash256(input), hashes.sha256(hashes.sha256(input)))
      t.end()
    })
  })
}

runTests(require('../bindings'))
runTests(require('../browser'))
runTests(require('../node'))
