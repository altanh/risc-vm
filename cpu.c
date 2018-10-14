#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "inst.h"
#include "mem.h"
#include "cpu.h"

void cpuInit(cpu_t *c) {
  size_t i;
  for(i = 0; i < CPU_REG_COUNT; ++i)
    c->reg[i] = 0U;

  c->pc = 0U;
}

void cpuPrint(cpu_t *c) {
  size_t i;
  for(i = 0; i < CPU_REG_COUNT; ++i)
    printf("x%02zd: 0x%016lx\n", i, c->reg[i]);

  printf(" pc: 0x%016lx\n", c->pc);
}

void cpuCycle(cpu_t *c, mem_t *mem) {
  assert(ALIGNED(c->pc, BASE_ALIGNMENT));

  static inst_t jtable[32] = {
    instLoad,   instLoadFp,      instUnsupported, instMiscMem, 
    instOpImm,  instAuipc,       instOpImm32,     instUnsupported,
    instStore,  instStoreFp,     instUnsupported, instAmo,
    instOp,     instLui,         instOp32,        instUnsupported,
    instMadd,   instMsub,        instNmsub,       instNmadd,
    instOpFp,   instUnsupported, instUnsupported, instUnsupported,
    instBranch, instJalr,        instUnsupported, instJal,
    instSystem, instUnsupported, instUnsupported, instUnsupported
  };

  uint32_t inst;
  if(!memRead(mem, c->pc, 4, (uint8_t*) &inst)) {
    fprintf(stderr, "error: failed to fetch next instruction\n");

    /* value? */
    return;
  }

  if((inst & 0x3) != 0x3) {
    fprintf(stderr, "error: encountered non-base instruction\n");

    exit(EXIT_FAILURE);

    return;
  }

  jtable[EXTRACT(inst, 2, 5)](inst, c, mem);
}

