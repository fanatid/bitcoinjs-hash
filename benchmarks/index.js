'use strict'
const bindings = require('../bindings')
const browser = require('../browser')
const node = require('../node')
const createHash = require('./create-hash')
const sprintf = require('sprintf-js').sprintf

const INPUT = Buffer.allocUnsafe(32)
const ITERATIONS = 2e5

function measure (fn) {
  const hrtime = process.hrtime()
  for (let i = 0; i < ITERATIONS; i++) fn(INPUT)
  const diff = process.hrtime(hrtime)
  return sprintf('%5.09fs', (diff[0] * 1e9 + diff[1]) / 1e9)
}

function run (alg) {
  console.log(`benchmarking ${alg}, input size: ${INPUT.length}, iterations: ${ITERATIONS} (lower is better)`)
  console.log('--------------------------------------------------')
  console.log(`bindings:            ${measure(bindings[alg])}`)
  console.log(`browser:             ${measure(browser[alg])}`)
  console.log(`node:                ${measure(node[alg])}`)
  console.log(`create-hash/browser: ${measure(createHash[alg])}`)
  console.log('==================================================')
}

const argv2 = process.argv[2]
const algs = argv2 ? [ argv2 ] : [ 'ripemd160', 'sha1', 'sha256', 'hash160', 'hash256' ]
for (let alg of algs) run(alg)
