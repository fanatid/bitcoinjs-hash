#ifndef _BITCOINJSHASH_SHA1_
# define _BITCOINJSHASH_SHA1_

#define ROTL1(x) (((x) << 1) | ((x) >> 31))
#define ROTL5(x) (((x) << 5) | ((x) >> 27))
#define ROTL30(x) (((x) << 30) | ((x) >> 2))
#define FN0(b, c, d) ((b & c) | ((~b) & d))
#define FN1(b, c, d) (b ^ c ^ d)
#define FN2(b, c, d) ((b & c) | (b & d) | (c & d))

#define BE32(p) ((((p) & 0xFF) << 24) | (((p) & 0xFF00) << 8) | (((p) & 0xFF0000) >> 8) | (((p) & 0xFF000000) >> 24))

static void sha1_update(uint32_t* state, uint32_t* words) {
  uint32_t a = state[0], b = state[1], c = state[2], d = state[3], e = state[4];

  for (size_t i = 0; i < 16; ++i) words[i] = BE32(words[i]);
  for (size_t i = 16; i < 80; ++i) words[i] = ROTL1(words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16]);

  for (size_t i = 0; i < 80; ++i) {
    uint32_t t;
    if (i < 20) {
      t = (e + FN0(b, c, d) + ROTL5(a) + words[i] + 0x5a827999);
    } else if (i < 40) {
      t = (e + FN1(b, c, d) + ROTL5(a) + words[i] + 0x6ed9eba1);
    } else if (i < 60) {
      t = (e + FN2(b, c, d) + ROTL5(a) + words[i] + 0x8f1bbcdc);
    } else { // i < 80
      t = (e + FN1(b, c, d) + ROTL5(a) + words[i] + 0xca62c1d6);
    }

    e = d;
    d = c;
    c = ROTL30(b);
    b = a;
    a = t;
  }

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;
  state[4] += e;
}

void sha1(unsigned char* output20, const unsigned char* input, size_t inputlen) {
  uint32_t state[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };
  uint32_t words[80] = { 0 };

  // consume data
  uint32_t offset = 0;
  for (; offset + 64 <= inputlen; offset += 64) {
    memcpy(((unsigned char*) words), input + offset, 64);
    sha1_update(state, words);
  }
  uint32_t blockOffset = inputlen - offset;
  if (blockOffset != 0) memcpy(((unsigned char*) words), input + offset, blockOffset);

  // create padding
  ((unsigned char*) words)[blockOffset++] = 0x80;
  if (blockOffset > 56) {
    while (blockOffset < 64) ((unsigned char*) words)[blockOffset++] = 0;
    sha1_update(state, words);
    blockOffset = 0;
  }

  while (blockOffset < 56) ((unsigned char*) words)[blockOffset++] = 0;
  words[14] = BE32(inputlen >> 29 << 8);
  words[15] = BE32(inputlen << 3);
  sha1_update(state, words);

  // produce hash
  for (uint8_t i = 0; i < 5; ++i) state[i] = BE32(state[i]);
  memcpy((void*) output20, (const void*) state, 20);
}

#undef BE32
#undef ROTL1
#undef ROTL5
#undef ROTL30
#undef FN0
#undef FN1
#undef FN2

#endif
