#ifndef _RISC_VM_INSTRUCTIONS_H_
#define _RISC_VM_INSTRUCTIONS_H_

#include "mem.h"
#include "cpu.h"

#define PARCEL_ALIGNMENT 2U
#define BASE_ALIGNMENT 4U

typedef void (*inst_t)(uint32_t, cpu_t*, mem_t*);

void instUnsupported(uint32_t inst, cpu_t *c, mem_t *mem);

void instLoad(uint32_t inst, cpu_t *c, mem_t *mem);
void instLoadFp(uint32_t inst, cpu_t *c, mem_t *mem);
void instStore(uint32_t inst, cpu_t *c, mem_t *mem);
void instStoreFp(uint32_t inst, cpu_t *c, mem_t *mem);
void instLui(uint32_t inst, cpu_t *c, mem_t *mem);
void instAuipc(uint32_t inst, cpu_t *c, mem_t *mem);
void instMiscMem(uint32_t inst, cpu_t *c, mem_t *mem);

void instAmo(uint32_t inst, cpu_t *c, mem_t *mem);

void instOpImm(uint32_t inst, cpu_t *c, mem_t *mem);
void instOpImm32(uint32_t inst, cpu_t *c, mem_t *mem);
void instOp(uint32_t inst, cpu_t *c, mem_t *mem);
void instOp32(uint32_t inst, cpu_t *c, mem_t *mem);
void instOpFp(uint32_t inst, cpu_t *c, mem_t *mem);

void instMadd(uint32_t inst, cpu_t *c, mem_t *mem);
void instNmadd(uint32_t inst, cpu_t *c, mem_t *mem);
void instMsub(uint32_t inst, cpu_t *c, mem_t *mem);
void instNmsub(uint32_t inst, cpu_t *c, mem_t *mem);

void instBranch(uint32_t inst, cpu_t *c, mem_t *mem);
void instJalr(uint32_t inst, cpu_t *c, mem_t *mem);
void instJal(uint32_t inst, cpu_t *c, mem_t *mem);
void instSystem(uint32_t inst, cpu_t *c, mem_t *mem);

#endif
