#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <assert.h>

#include "cpu.h"
#include "mem.h"
#include "inst.h"

#define MEM_SIZE 1024U

int main(int argc, char **argv) {
  cpu_t c;
  mem_t mem;

  cpuInit(&c);
  memAlloc(&mem, MEM_SIZE);

  uint32_t loadinst = 0x83;
  uint32_t inst = 0x2081B3;
  uint32_t inst2 = 0x31C1B3;

  memWrite(&mem, 0, 4, (uint8_t*) &loadinst);
  memWrite(&mem, 4, 4, (uint8_t*) &inst);
  memWrite(&mem, 8, 4, (uint8_t*) &inst2);

  cpuPrint(&c);
  cpuCycle(&c, &mem);
  cpuPrint(&c);
  cpuCycle(&c, &mem);
  cpuPrint(&c);
  cpuCycle(&c, &mem);
  cpuPrint(&c);

  memDump(&mem);

  return EXIT_SUCCESS;
}

