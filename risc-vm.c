#include <inttypes.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "cpu.h"
#include "mem.h"
#include "inst.h"

#define MEM_SIZE 4096U

uint32_t revBitsU32(uint32_t n) {
  uint32_t res = 0;

  uint8_t i;
  for(i = 0; i < 32; ++i)
    if((n & (1 << i)))
      res |= 1 << (31 - i);

  return res;
}

uint32_t binStrToU32(const char *s) {
  uint32_t res = 0;
  char c;

  uint8_t i = 0;
  while((c = *s++)) {
    /* ignore other chars */
    if(c == '0' || c == '1')
      res |= (c - '0') << i++;
  }
  
  return revBitsU32(res);
}

int main(int argc, char **argv) {
  cpu_t c;
  mem_t mem;

  cpuInit(&c);
  memAlloc(&mem, MEM_SIZE);

  uint8_t inc = 1;
  uint8_t count = 10;

  /*
   * 0x00:
   * lbu x1, x0 + 0xFE
   * lbu x3, x0 + 0xFF
   * xor x2, x2, x2
   *
   * 0x10:
   * add x2, x2, x1
   * bltu x2, x3, 0x00
   */
  const uint32_t prog[] = {
    binStrToU32("000011111110 00000 100 00001 0000011"),
    binStrToU32("000011111111 00000 100 00011 0000011"),
    binStrToU32("0000000 00010 00010 100 00010 0110011"),
    binStrToU32("0000000 00010 00001 000 00010 0110011"),
    binStrToU32("1111111 00011 00010 110 11101 1100011")
  };

  memWrite(&mem, 0, sizeof(prog), (uint8_t*) &prog);
  memWrite(&mem, 0xFE, 1, &inc);
  memWrite(&mem, 0xFF, 1, &count);

  uint64_t i = 0;
  while(cpuCycle(&c, &mem) == CPU_CYCLE_OK) {
    printf("cycle %" PRIu64 "\n", i++);
    cpuPrint(&c);
  }

  memDump(&mem);

  return EXIT_SUCCESS;
}

