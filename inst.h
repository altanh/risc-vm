#ifndef _RISC_VM_INSTRUCTIONS_H_
#define _RISC_VM_INSTRUCTIONS_H_

#include "util.h"
#include "mem.h"
#include "cpu.h"

#define DECODE_FUNCT3(inst) EXTRACT((inst), 12, 3)
#define DECODE_FUNCT7(inst) EXTRACT((inst), 25, 7)
#define DECODE_RD(inst) EXTRACT((inst), 7, 5)
#define DECODE_RS1(inst) EXTRACT((inst), 15, 5)
#define DECODE_RS2(inst) EXTRACT((inst), 20, 5)

/* NOT SIGN EXTENDED */

/* 12 bit immediates */
#define DECODE_IMM_I(inst) EXTRACT((inst), 20, 12)
#define DECODE_IMM_S(inst) ((EXTRACT((inst), 25, 7) << 5) | EXTRACT((inst), 7, 5))
#define DECODE_IMM_B(inst) ((EXTRACT((inst), 31, 1) << 11) | (EXTRACT((inst), 7, 1) << 10) | (EXTRACT((inst), 25, 6) << 4) | EXTRACT((inst), 8, 4))
/* 20 bit immediates */
#define DECODE_IMM_U(inst) EXTRACT((inst), 12, 20)
#define DECODE_IMM_J(inst) ((EXTRACT((inst), 31, 1) << 19) | (EXTRACT((inst), 12, 8) << 11) | (EXTRACT((inst), 20, 1) << 10) | EXTRACT((inst), 21, 10))

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
