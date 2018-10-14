#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "inst.h"

void testExtract();
void testSignExtend();
void testDecode();

int main(int argc, char **argv) {
  testExtract();
  testSignExtend();
  testDecode();

  printf("all assertions passed.\n");
}

void testExtract() {
  const uint32_t deadbeef = 0xdeadbeef;

  assert(EXTRACT(deadbeef, 0, 16) == 0xbeef);
  assert(EXTRACT(deadbeef, 16, 16) == 0xdead);
  assert(EXTRACT(deadbeef, 8, 16) == 0xadbe);
  assert(EXTRACT(deadbeef, 28, 4) == 0xd);
  assert(EXTRACT(deadbeef, 31, 1) == 0x1);
  assert(EXTRACT(deadbeef, 0, 1) == 0x1);
}

void testSignExtend() {
  const uint64_t deadbeef = 0xdeadbeef;
  const uint64_t byte_neg_one = 0xFF;
  const uint64_t byte_max = 0x7F;

  assert(SIGN_EXTEND_64U(deadbeef, 32) == 0xffffffffdeadbeef);
  assert(SIGN_EXTEND_64U(byte_neg_one, 8) == UINT64_MAX);
  assert(SIGN_EXTEND_64U(byte_max, 8) == 0x7F);
}

void testDecode() {

}
