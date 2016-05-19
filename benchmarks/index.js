'use strict'
var bindings = require('../bindings')
var browser = require('../browser')
var node = require('../node')

var INPUT = new Buffer(32)

function measure (fn) {
  var hrtime = process.hrtime()
  for (var i = 0; i < 1e6; i++) fn(INPUT)
  var diff = process.hrtime(hrtime)
  return diff[0] * 1e9 + diff[1]
}

function run (alg) {
  console.log(`benchmarking ${alg}, input size: ${INPUT.length} (lower is better)`)
  console.log('--------------------------------------------------')
  console.log(`bindings: ${measure(bindings[alg])}`)
  console.log(`browser:  ${measure(browser[alg])}`)
  console.log(`node:     ${measure(node[alg])}`)
  console.log('==================================================')
}

var argv2 = process.argv[2]
var algs = argv2 ? [ argv2 ] : [ 'ripemd160', 'sha1', 'sha256', 'hash160', 'hash256' ]
for (let alg of algs) run(alg)
