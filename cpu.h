#ifndef _RISC_VM_CPU_H_
#define _RISC_VM_CPU_H_

#include <stdint.h>

#include "mem.h"

#define CPU_REG_COUNT 32

typedef struct {
  uint64_t reg[CPU_REG_COUNT];
  uint64_t pc;
} cpu_t;

void cpuInit(cpu_t *c);
void cpuPrint(cpu_t *c);

void cpuCycle(cpu_t *c, mem_t *mem);

#endif
