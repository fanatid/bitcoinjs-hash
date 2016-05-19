#ifndef _BITCOINJSHASH_RIPEMD160_
# define _BITCOINJSHASH_RIPEMD160_

#define ROTL(x, n) (((x) << n) | ((x) >> (32 - n)))
#define FN1(a, b, c, d, e, m, k, s) (ROTL(a + (b ^ c ^ d) + m + k, s) + e)
#define FN2(a, b, c, d, e, m, k, s) (ROTL(a + ((b & c) | ((~b) & d)) + m + k, s) + e)
#define FN3(a, b, c, d, e, m, k, s) (ROTL(a + ((b | (~c)) ^ d) + m + k, s) + e)
#define FN4(a, b, c, d, e, m, k, s) (ROTL(a + ((b & d) | (c & (~d))) + m + k, s) + e)
#define FN5(a, b, c, d, e, m, k, s) (ROTL(a + (b ^ (c | (~d))) + m + k, s) + e)

static void ripemd160_update(uint32_t* state, uint32_t* words) {
  uint32_t al = state[0];
  uint32_t bl = state[1];
  uint32_t cl = state[2];
  uint32_t dl = state[3];
  uint32_t el = state[4];

  // Mj = 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
  // K = 0x00000000
  // Sj = 11, 14, 15, 12, 5, 8, 7, 9, 11, 13, 14, 15, 6, 7, 9, 8
  al = FN1(al, bl, cl, dl, el, words[0], 0x00000000, 11); cl = ROTL(cl, 10);
  el = FN1(el, al, bl, cl, dl, words[1], 0x00000000, 14); bl = ROTL(bl, 10);
  dl = FN1(dl, el, al, bl, cl, words[2], 0x00000000, 15); al = ROTL(al, 10);
  cl = FN1(cl, dl, el, al, bl, words[3], 0x00000000, 12); el = ROTL(el, 10);
  bl = FN1(bl, cl, dl, el, al, words[4], 0x00000000, 5); dl = ROTL(dl, 10);
  al = FN1(al, bl, cl, dl, el, words[5], 0x00000000, 8); cl = ROTL(cl, 10);
  el = FN1(el, al, bl, cl, dl, words[6], 0x00000000, 7); bl = ROTL(bl, 10);
  dl = FN1(dl, el, al, bl, cl, words[7], 0x00000000, 9); al = ROTL(al, 10);
  cl = FN1(cl, dl, el, al, bl, words[8], 0x00000000, 11); el = ROTL(el, 10);
  bl = FN1(bl, cl, dl, el, al, words[9], 0x00000000, 13); dl = ROTL(dl, 10);
  al = FN1(al, bl, cl, dl, el, words[10], 0x00000000, 14); cl = ROTL(cl, 10);
  el = FN1(el, al, bl, cl, dl, words[11], 0x00000000, 15); bl = ROTL(bl, 10);
  dl = FN1(dl, el, al, bl, cl, words[12], 0x00000000, 6); al = ROTL(al, 10);
  cl = FN1(cl, dl, el, al, bl, words[13], 0x00000000, 7); el = ROTL(el, 10);
  bl = FN1(bl, cl, dl, el, al, words[14], 0x00000000, 9); dl = ROTL(dl, 10);
  al = FN1(al, bl, cl, dl, el, words[15], 0x00000000, 8); cl = ROTL(cl, 10);

  // Mj = 7, 4, 13, 1, 10, 6, 15, 3, 12, 0, 9, 5, 2, 14, 11, 8
  // K = 0x5a827999
  // Sj = 7, 6, 8, 13, 11, 9, 7, 15, 7, 12, 15, 9, 11, 7, 13, 12
  el = FN2(el, al, bl, cl, dl, words[7], 0x5a827999, 7); bl = ROTL(bl, 10);
  dl = FN2(dl, el, al, bl, cl, words[4], 0x5a827999, 6); al = ROTL(al, 10);
  cl = FN2(cl, dl, el, al, bl, words[13], 0x5a827999, 8); el = ROTL(el, 10);
  bl = FN2(bl, cl, dl, el, al, words[1], 0x5a827999, 13); dl = ROTL(dl, 10);
  al = FN2(al, bl, cl, dl, el, words[10], 0x5a827999, 11); cl = ROTL(cl, 10);
  el = FN2(el, al, bl, cl, dl, words[6], 0x5a827999, 9); bl = ROTL(bl, 10);
  dl = FN2(dl, el, al, bl, cl, words[15], 0x5a827999, 7); al = ROTL(al, 10);
  cl = FN2(cl, dl, el, al, bl, words[3], 0x5a827999, 15); el = ROTL(el, 10);
  bl = FN2(bl, cl, dl, el, al, words[12], 0x5a827999, 7); dl = ROTL(dl, 10);
  al = FN2(al, bl, cl, dl, el, words[0], 0x5a827999, 12); cl = ROTL(cl, 10);
  el = FN2(el, al, bl, cl, dl, words[9], 0x5a827999, 15); bl = ROTL(bl, 10);
  dl = FN2(dl, el, al, bl, cl, words[5], 0x5a827999, 9); al = ROTL(al, 10);
  cl = FN2(cl, dl, el, al, bl, words[2], 0x5a827999, 11); el = ROTL(el, 10);
  bl = FN2(bl, cl, dl, el, al, words[14], 0x5a827999, 7); dl = ROTL(dl, 10);
  al = FN2(al, bl, cl, dl, el, words[11], 0x5a827999, 13); cl = ROTL(cl, 10);
  el = FN2(el, al, bl, cl, dl, words[8], 0x5a827999, 12); bl = ROTL(bl, 10);

  // Mj = 3, 10, 14, 4, 9, 15, 8, 1, 2, 7, 0, 6, 13, 11, 5, 12
  // K = 0x6ed9eba1
  // Sj = 11, 13, 6, 7, 14, 9, 13, 15, 14, 8, 13, 6, 5, 12, 7, 5
  dl = FN3(dl, el, al, bl, cl, words[3], 0x6ed9eba1, 11); al = ROTL(al, 10);
  cl = FN3(cl, dl, el, al, bl, words[10], 0x6ed9eba1, 13); el = ROTL(el, 10);
  bl = FN3(bl, cl, dl, el, al, words[14], 0x6ed9eba1, 6); dl = ROTL(dl, 10);
  al = FN3(al, bl, cl, dl, el, words[4], 0x6ed9eba1, 7); cl = ROTL(cl, 10);
  el = FN3(el, al, bl, cl, dl, words[9], 0x6ed9eba1, 14); bl = ROTL(bl, 10);
  dl = FN3(dl, el, al, bl, cl, words[15], 0x6ed9eba1, 9); al = ROTL(al, 10);
  cl = FN3(cl, dl, el, al, bl, words[8], 0x6ed9eba1, 13); el = ROTL(el, 10);
  bl = FN3(bl, cl, dl, el, al, words[1], 0x6ed9eba1, 15); dl = ROTL(dl, 10);
  al = FN3(al, bl, cl, dl, el, words[2], 0x6ed9eba1, 14); cl = ROTL(cl, 10);
  el = FN3(el, al, bl, cl, dl, words[7], 0x6ed9eba1, 8); bl = ROTL(bl, 10);
  dl = FN3(dl, el, al, bl, cl, words[0], 0x6ed9eba1, 13); al = ROTL(al, 10);
  cl = FN3(cl, dl, el, al, bl, words[6], 0x6ed9eba1, 6); el = ROTL(el, 10);
  bl = FN3(bl, cl, dl, el, al, words[13], 0x6ed9eba1, 5); dl = ROTL(dl, 10);
  al = FN3(al, bl, cl, dl, el, words[11], 0x6ed9eba1, 12); cl = ROTL(cl, 10);
  el = FN3(el, al, bl, cl, dl, words[5], 0x6ed9eba1, 7); bl = ROTL(bl, 10);
  dl = FN3(dl, el, al, bl, cl, words[12], 0x6ed9eba1, 5); al = ROTL(al, 10);

  // Mj = 1, 9, 11, 10, 0, 8, 12, 4, 13, 3, 7, 15, 14, 5, 6, 2
  // K = 0x8f1bbcdc
  // Sj = 11, 12, 14, 15, 14, 15, 9, 8, 9, 14, 5, 6, 8, 6, 5, 12
  cl = FN4(cl, dl, el, al, bl, words[1], 0x8f1bbcdc, 11); el = ROTL(el, 10);
  bl = FN4(bl, cl, dl, el, al, words[9], 0x8f1bbcdc, 12); dl = ROTL(dl, 10);
  al = FN4(al, bl, cl, dl, el, words[11], 0x8f1bbcdc, 14); cl = ROTL(cl, 10);
  el = FN4(el, al, bl, cl, dl, words[10], 0x8f1bbcdc, 15); bl = ROTL(bl, 10);
  dl = FN4(dl, el, al, bl, cl, words[0], 0x8f1bbcdc, 14); al = ROTL(al, 10);
  cl = FN4(cl, dl, el, al, bl, words[8], 0x8f1bbcdc, 15); el = ROTL(el, 10);
  bl = FN4(bl, cl, dl, el, al, words[12], 0x8f1bbcdc, 9); dl = ROTL(dl, 10);
  al = FN4(al, bl, cl, dl, el, words[4], 0x8f1bbcdc, 8); cl = ROTL(cl, 10);
  el = FN4(el, al, bl, cl, dl, words[13], 0x8f1bbcdc, 9); bl = ROTL(bl, 10);
  dl = FN4(dl, el, al, bl, cl, words[3], 0x8f1bbcdc, 14); al = ROTL(al, 10);
  cl = FN4(cl, dl, el, al, bl, words[7], 0x8f1bbcdc, 5); el = ROTL(el, 10);
  bl = FN4(bl, cl, dl, el, al, words[15], 0x8f1bbcdc, 6); dl = ROTL(dl, 10);
  al = FN4(al, bl, cl, dl, el, words[14], 0x8f1bbcdc, 8); cl = ROTL(cl, 10);
  el = FN4(el, al, bl, cl, dl, words[5], 0x8f1bbcdc, 6); bl = ROTL(bl, 10);
  dl = FN4(dl, el, al, bl, cl, words[6], 0x8f1bbcdc, 5); al = ROTL(al, 10);
  cl = FN4(cl, dl, el, al, bl, words[2], 0x8f1bbcdc, 12); el = ROTL(el, 10);

  // Mj = 4, 0, 5, 9, 7, 12, 2, 10, 14, 1, 3, 8, 11, 6, 15, 13
  // K = 0xa953fd4e
  // Sj = 9, 15, 5, 11, 6, 8, 13, 12, 5, 12, 13, 14, 11, 8, 5, 6
  bl = FN5(bl, cl, dl, el, al, words[4], 0xa953fd4e, 9); dl = ROTL(dl, 10);
  al = FN5(al, bl, cl, dl, el, words[0], 0xa953fd4e, 15); cl = ROTL(cl, 10);
  el = FN5(el, al, bl, cl, dl, words[5], 0xa953fd4e, 5); bl = ROTL(bl, 10);
  dl = FN5(dl, el, al, bl, cl, words[9], 0xa953fd4e, 11); al = ROTL(al, 10);
  cl = FN5(cl, dl, el, al, bl, words[7], 0xa953fd4e, 6); el = ROTL(el, 10);
  bl = FN5(bl, cl, dl, el, al, words[12], 0xa953fd4e, 8); dl = ROTL(dl, 10);
  al = FN5(al, bl, cl, dl, el, words[2], 0xa953fd4e, 13); cl = ROTL(cl, 10);
  el = FN5(el, al, bl, cl, dl, words[10], 0xa953fd4e, 12); bl = ROTL(bl, 10);
  dl = FN5(dl, el, al, bl, cl, words[14], 0xa953fd4e, 5); al = ROTL(al, 10);
  cl = FN5(cl, dl, el, al, bl, words[1], 0xa953fd4e, 12); el = ROTL(el, 10);
  bl = FN5(bl, cl, dl, el, al, words[3], 0xa953fd4e, 13); dl = ROTL(dl, 10);
  al = FN5(al, bl, cl, dl, el, words[8], 0xa953fd4e, 14); cl = ROTL(cl, 10);
  el = FN5(el, al, bl, cl, dl, words[11], 0xa953fd4e, 11); bl = ROTL(bl, 10);
  dl = FN5(dl, el, al, bl, cl, words[6], 0xa953fd4e, 8); al = ROTL(al, 10);
  cl = FN5(cl, dl, el, al, bl, words[15], 0xa953fd4e, 5); el = ROTL(el, 10);
  bl = FN5(bl, cl, dl, el, al, words[13], 0xa953fd4e, 6); dl = ROTL(dl, 10);

  uint32_t ar = state[0];
  uint32_t br = state[1];
  uint32_t cr = state[2];
  uint32_t dr = state[3];
  uint32_t er = state[4];

  // M'j = 5, 14, 7, 0, 9, 2, 11, 4, 13, 6, 15, 8, 1, 10, 3, 12
  // K' = 0x50a28be6
  // S'j = 8, 9, 9, 11, 13, 15, 15, 5, 7, 7, 8, 11, 14, 14, 12, 6
  ar = FN5(ar, br, cr, dr, er, words[5], 0x50a28be6, 8); cr = ROTL(cr, 10);
  er = FN5(er, ar, br, cr, dr, words[14], 0x50a28be6, 9); br = ROTL(br, 10);
  dr = FN5(dr, er, ar, br, cr, words[7], 0x50a28be6, 9); ar = ROTL(ar, 10);
  cr = FN5(cr, dr, er, ar, br, words[0], 0x50a28be6, 11); er = ROTL(er, 10);
  br = FN5(br, cr, dr, er, ar, words[9], 0x50a28be6, 13); dr = ROTL(dr, 10);
  ar = FN5(ar, br, cr, dr, er, words[2], 0x50a28be6, 15); cr = ROTL(cr, 10);
  er = FN5(er, ar, br, cr, dr, words[11], 0x50a28be6, 15); br = ROTL(br, 10);
  dr = FN5(dr, er, ar, br, cr, words[4], 0x50a28be6, 5); ar = ROTL(ar, 10);
  cr = FN5(cr, dr, er, ar, br, words[13], 0x50a28be6, 7); er = ROTL(er, 10);
  br = FN5(br, cr, dr, er, ar, words[6], 0x50a28be6, 7); dr = ROTL(dr, 10);
  ar = FN5(ar, br, cr, dr, er, words[15], 0x50a28be6, 8); cr = ROTL(cr, 10);
  er = FN5(er, ar, br, cr, dr, words[8], 0x50a28be6, 11); br = ROTL(br, 10);
  dr = FN5(dr, er, ar, br, cr, words[1], 0x50a28be6, 14); ar = ROTL(ar, 10);
  cr = FN5(cr, dr, er, ar, br, words[10], 0x50a28be6, 14); er = ROTL(er, 10);
  br = FN5(br, cr, dr, er, ar, words[3], 0x50a28be6, 12); dr = ROTL(dr, 10);
  ar = FN5(ar, br, cr, dr, er, words[12], 0x50a28be6, 6); cr = ROTL(cr, 10);

  // M'j = 6, 11, 3, 7, 0, 13, 5, 10, 14, 15, 8, 12, 4, 9, 1, 2
  // K' = 0x5c4dd124
  // S'j = 9, 13, 15, 7, 12, 8, 9, 11, 7, 7, 12, 7, 6, 15, 13, 11
  er = FN4(er, ar, br, cr, dr, words[6], 0x5c4dd124, 9); br = ROTL(br, 10);
  dr = FN4(dr, er, ar, br, cr, words[11], 0x5c4dd124, 13); ar = ROTL(ar, 10);
  cr = FN4(cr, dr, er, ar, br, words[3], 0x5c4dd124, 15); er = ROTL(er, 10);
  br = FN4(br, cr, dr, er, ar, words[7], 0x5c4dd124, 7); dr = ROTL(dr, 10);
  ar = FN4(ar, br, cr, dr, er, words[0], 0x5c4dd124, 12); cr = ROTL(cr, 10);
  er = FN4(er, ar, br, cr, dr, words[13], 0x5c4dd124, 8); br = ROTL(br, 10);
  dr = FN4(dr, er, ar, br, cr, words[5], 0x5c4dd124, 9); ar = ROTL(ar, 10);
  cr = FN4(cr, dr, er, ar, br, words[10], 0x5c4dd124, 11); er = ROTL(er, 10);
  br = FN4(br, cr, dr, er, ar, words[14], 0x5c4dd124, 7); dr = ROTL(dr, 10);
  ar = FN4(ar, br, cr, dr, er, words[15], 0x5c4dd124, 7); cr = ROTL(cr, 10);
  er = FN4(er, ar, br, cr, dr, words[8], 0x5c4dd124, 12); br = ROTL(br, 10);
  dr = FN4(dr, er, ar, br, cr, words[12], 0x5c4dd124, 7); ar = ROTL(ar, 10);
  cr = FN4(cr, dr, er, ar, br, words[4], 0x5c4dd124, 6); er = ROTL(er, 10);
  br = FN4(br, cr, dr, er, ar, words[9], 0x5c4dd124, 15); dr = ROTL(dr, 10);
  ar = FN4(ar, br, cr, dr, er, words[1], 0x5c4dd124, 13); cr = ROTL(cr, 10);
  er = FN4(er, ar, br, cr, dr, words[2], 0x5c4dd124, 11); br = ROTL(br, 10);

  // M'j = 15, 5, 1, 3, 7, 14, 6, 9, 11, 8, 12, 2, 10, 0, 4, 13
  // K' = 0x6d703ef3
  // S'j = 9, 7, 15, 11, 8, 6, 6, 14, 12, 13, 5, 14, 13, 13, 7, 5
  dr = FN3(dr, er, ar, br, cr, words[15], 0x6d703ef3, 9); ar = ROTL(ar, 10);
  cr = FN3(cr, dr, er, ar, br, words[5], 0x6d703ef3, 7); er = ROTL(er, 10);
  br = FN3(br, cr, dr, er, ar, words[1], 0x6d703ef3, 15); dr = ROTL(dr, 10);
  ar = FN3(ar, br, cr, dr, er, words[3], 0x6d703ef3, 11); cr = ROTL(cr, 10);
  er = FN3(er, ar, br, cr, dr, words[7], 0x6d703ef3, 8); br = ROTL(br, 10);
  dr = FN3(dr, er, ar, br, cr, words[14], 0x6d703ef3, 6); ar = ROTL(ar, 10);
  cr = FN3(cr, dr, er, ar, br, words[6], 0x6d703ef3, 6); er = ROTL(er, 10);
  br = FN3(br, cr, dr, er, ar, words[9], 0x6d703ef3, 14); dr = ROTL(dr, 10);
  ar = FN3(ar, br, cr, dr, er, words[11], 0x6d703ef3, 12); cr = ROTL(cr, 10);
  er = FN3(er, ar, br, cr, dr, words[8], 0x6d703ef3, 13); br = ROTL(br, 10);
  dr = FN3(dr, er, ar, br, cr, words[12], 0x6d703ef3, 5); ar = ROTL(ar, 10);
  cr = FN3(cr, dr, er, ar, br, words[2], 0x6d703ef3, 14); er = ROTL(er, 10);
  br = FN3(br, cr, dr, er, ar, words[10], 0x6d703ef3, 13); dr = ROTL(dr, 10);
  ar = FN3(ar, br, cr, dr, er, words[0], 0x6d703ef3, 13); cr = ROTL(cr, 10);
  er = FN3(er, ar, br, cr, dr, words[4], 0x6d703ef3, 7); br = ROTL(br, 10);
  dr = FN3(dr, er, ar, br, cr, words[13], 0x6d703ef3, 5); ar = ROTL(ar, 10);

  // M'j = 8, 6, 4, 1, 3, 11, 15, 0, 5, 12, 2, 13, 9, 7, 10, 14
  // K' = 0x7a6d76e9
  // S'j = 15, 5, 8, 11, 14, 14, 6, 14, 6, 9, 12, 9, 12, 5, 15, 8
  cr = FN2(cr, dr, er, ar, br, words[8], 0x7a6d76e9, 15); er = ROTL(er, 10);
  br = FN2(br, cr, dr, er, ar, words[6], 0x7a6d76e9, 5); dr = ROTL(dr, 10);
  ar = FN2(ar, br, cr, dr, er, words[4], 0x7a6d76e9, 8); cr = ROTL(cr, 10);
  er = FN2(er, ar, br, cr, dr, words[1], 0x7a6d76e9, 11); br = ROTL(br, 10);
  dr = FN2(dr, er, ar, br, cr, words[3], 0x7a6d76e9, 14); ar = ROTL(ar, 10);
  cr = FN2(cr, dr, er, ar, br, words[11], 0x7a6d76e9, 14); er = ROTL(er, 10);
  br = FN2(br, cr, dr, er, ar, words[15], 0x7a6d76e9, 6); dr = ROTL(dr, 10);
  ar = FN2(ar, br, cr, dr, er, words[0], 0x7a6d76e9, 14); cr = ROTL(cr, 10);
  er = FN2(er, ar, br, cr, dr, words[5], 0x7a6d76e9, 6); br = ROTL(br, 10);
  dr = FN2(dr, er, ar, br, cr, words[12], 0x7a6d76e9, 9); ar = ROTL(ar, 10);
  cr = FN2(cr, dr, er, ar, br, words[2], 0x7a6d76e9, 12); er = ROTL(er, 10);
  br = FN2(br, cr, dr, er, ar, words[13], 0x7a6d76e9, 9); dr = ROTL(dr, 10);
  ar = FN2(ar, br, cr, dr, er, words[9], 0x7a6d76e9, 12); cr = ROTL(cr, 10);
  er = FN2(er, ar, br, cr, dr, words[7], 0x7a6d76e9, 5); br = ROTL(br, 10);
  dr = FN2(dr, er, ar, br, cr, words[10], 0x7a6d76e9, 15); ar = ROTL(ar, 10);
  cr = FN2(cr, dr, er, ar, br, words[14], 0x7a6d76e9, 8); er = ROTL(er, 10);

  // M'j = 12, 15, 10, 4, 1, 5, 8, 7, 6, 2, 13, 14, 0, 3, 9, 11
  // K' = 0x00000000
  // S'j = 8, 5, 12, 9, 12, 5, 14, 6, 8, 13, 6, 5, 15, 13, 11, 11
  br = FN1(br, cr, dr, er, ar, words[12], 0x00000000, 8); dr = ROTL(dr, 10);
  ar = FN1(ar, br, cr, dr, er, words[15], 0x00000000, 5); cr = ROTL(cr, 10);
  er = FN1(er, ar, br, cr, dr, words[10], 0x00000000, 12); br = ROTL(br, 10);
  dr = FN1(dr, er, ar, br, cr, words[4], 0x00000000, 9); ar = ROTL(ar, 10);
  cr = FN1(cr, dr, er, ar, br, words[1], 0x00000000, 12); er = ROTL(er, 10);
  br = FN1(br, cr, dr, er, ar, words[5], 0x00000000, 5); dr = ROTL(dr, 10);
  ar = FN1(ar, br, cr, dr, er, words[8], 0x00000000, 14); cr = ROTL(cr, 10);
  er = FN1(er, ar, br, cr, dr, words[7], 0x00000000, 6); br = ROTL(br, 10);
  dr = FN1(dr, er, ar, br, cr, words[6], 0x00000000, 8); ar = ROTL(ar, 10);
  cr = FN1(cr, dr, er, ar, br, words[2], 0x00000000, 13); er = ROTL(er, 10);
  br = FN1(br, cr, dr, er, ar, words[13], 0x00000000, 6); dr = ROTL(dr, 10);
  ar = FN1(ar, br, cr, dr, er, words[14], 0x00000000, 5); cr = ROTL(cr, 10);
  er = FN1(er, ar, br, cr, dr, words[0], 0x00000000, 15); br = ROTL(br, 10);
  dr = FN1(dr, er, ar, br, cr, words[3], 0x00000000, 13); ar = ROTL(ar, 10);
  cr = FN1(cr, dr, er, ar, br, words[9], 0x00000000, 11); er = ROTL(er, 10);
  br = FN1(br, cr, dr, er, ar, words[11], 0x00000000, 11); dr = ROTL(dr, 10);

  // change state
  uint32_t t = state[1] + cl + dr;
  state[1] = state[2] + dl + er;
  state[2] = state[3] + el + ar;
  state[3] = state[4] + al + br;
  state[4] = state[0] + bl + cr;
  state[0] = t;
}

void ripemd160(unsigned char* output20, const unsigned char* input, size_t inputlen) {
  // init state
  uint32_t state[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };
  uint32_t words[16] = { 0 };

  // consume data
  uint32_t offset = 0;
  for (; offset + 64 <= inputlen; offset += 64) {
    memcpy(((unsigned char*) words), input + offset, 64);
    ripemd160_update(state, words);
  }
  uint32_t blockOffset = inputlen - offset;
  if (blockOffset != 0) memcpy(((unsigned char*) words), input + offset, blockOffset);

  // create padding
  ((unsigned char*) words)[blockOffset++] = 0x80;
  if (blockOffset > 56) {
    while (blockOffset < 64) ((unsigned char*) words)[blockOffset++] = 0;
    ripemd160_update(state, words);
    blockOffset = 0;
  }

  while (blockOffset < 56) ((unsigned char*) words)[blockOffset++] = 0;
  words[14] = inputlen << 3;
  words[15] = inputlen >> 29 << 8;
  ripemd160_update(state, words);

  // produce hash
  for (uint8_t i = 0; i < 5; ++i) words[i] = state[i];
  memcpy((void*) output20, (const void*) words, 20);
}

#undef FN5
#undef FN4
#undef FN3
#undef FN2
#undef FN1
#undef ROTL

#endif
