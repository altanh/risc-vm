#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "inst.h"
#include "util.h"
#include "cpu.h"
#include "mem.h"

#define OP_ADD  0x000
#define OP_SUB  0x100
#define OP_SLL  0x001
#define OP_SLT  0x002
#define OP_SLTU 0x003
#define OP_XOR  0x004
#define OP_SRL  0x005
#define OP_SRA  0x105
#define OP_OR   0x006
#define OP_AND  0x007

#define BRANCH_BEQ 0x0
#define BRANCH_BNE 0x1
#define BRANCH_BLT 0x4
#define BRANCH_BGE 0x5
#define BRANCH_BLTU 0x6
#define BRANCH_BGEU 0x7

#define LOAD_LB 0x0
#define LOAD_LH 0x1
#define LOAD_LW 0x2
#define LOAD_LD 0x3
#define LOAD_LBU 0x4
#define LOAD_LHU 0x5
#define LOAD_LWU 0x6

void instUnsupported(uint32_t inst, cpu_t *c, mem_t *mem) {
  fprintf(stderr, "error: unsupported instruction 0x%032x\n", inst);

  exit(EXIT_FAILURE);
}

void instLoad(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t funct3 = DECODE_FUNCT3(inst); 
  uint32_t rd = DECODE_RD(inst);
  uint32_t rs1 = DECODE_RS1(inst);
  uint64_t offset = SIGN_EXTEND_64U(DECODE_IMM_I(inst), 12);

  uint32_t w;
  uint16_t h;
  uint8_t b;

  /* need to see if sign extension works like I think it does */
  switch(funct3) {
    case LOAD_LB:
      memRead(mem, c->reg[rs1] + offset, 1, &b);
      c->reg[rd] = SIGN_EXTEND_64U((uint64_t) b, 8);
      break;
    case LOAD_LH:
      memRead(mem, c->reg[rs1] + offset, 2, (uint8_t*) &h);
      c->reg[rd] = SIGN_EXTEND_64U((uint64_t) h, 16);
      break;
    case LOAD_LW:
      memRead(mem, c->reg[rs1] + offset, 4, (uint8_t*) &w);
      c->reg[rd] = SIGN_EXTEND_64U((uint64_t) w, 32);
      break;
    case LOAD_LBU:
      memRead(mem, c->reg[rs1] + offset, 1, &b);
      c->reg[rd] = (uint64_t) b;
      break;
    case LOAD_LHU:
      memRead(mem, c->reg[rs1] + offset, 2, (uint8_t*) &h);
      c->reg[rd] = (uint64_t) h;
      break;
    case LOAD_LWU:
      memRead(mem, c->reg[rs1] + offset, 4, (uint8_t*) &w);
      c->reg[rd] = (uint64_t) w;
    case LOAD_LD:
      memRead(mem, c->reg[rs1] + offset, 8, (uint8_t*) &c->reg[rd]);
      break;
    default:
      instUnsupported(inst, c, mem);
      break;
  }

  c->reg[0] = 0;
  c->pc += 4;
}

void instLoadFp(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instStore(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instStoreFp(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instLui(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instAuipc(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instMiscMem(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instAmo(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instOpImm(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instOpImm32(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instOp(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t op = (DECODE_FUNCT7(inst) << 3) | DECODE_FUNCT3(inst);
  uint32_t rd = DECODE_RD(inst);
  uint32_t rs1 = DECODE_RS1(inst);
  uint32_t rs2 = DECODE_RS2(inst);

  switch(op) {
    case OP_ADD:
      printf("add x%u, x%u, x%u\n", rd, rs1, rs2);
      c->reg[rd] = c->reg[rs1] + c->reg[rs2];
      break;
    case OP_SUB:
      c->reg[rd] = c->reg[rs1] + (~c->reg[rs2] + 1);
      break;
    case OP_SLL:
      c->reg[rd] = c->reg[rs1] << EXTRACT(c->reg[rs2], 0, 6);
      break;
    case OP_SLT:
      c->reg[rd] = !!(((int64_t) c->reg[rs1]) < ((int64_t) c->reg[rs2]));
      break;
    case OP_SLTU:
      c->reg[rd] = !!(c->reg[rs1] < c->reg[rs2]);
      break;
    case OP_XOR:
      c->reg[rd] = c->reg[rs1] ^ c->reg[rs2];
      break;
    case OP_SRL:
      c->reg[rd] = c->reg[rs1] >> EXTRACT(c->reg[rs2], 0, 6);
      break;
    case OP_SRA:
      c->reg[rd] = (uint64_t) (((int64_t) c->reg[rs1]) >> EXTRACT(c->reg[rs2], 0, 6));
      break;
    case OP_OR:
      c->reg[rd] = c->reg[rs1] | c->reg[rs2];
      break;
    case OP_AND:
      c->reg[rd] = c->reg[rs1] & c->reg[rs2];
      break;
    default:
      instUnsupported(inst, c, mem);
      break;
  }

  /* betting this is faster than having a rd == 0 condition everywhere */
  c->reg[0] = 0;
  c->pc += 4;
}

void instOp32(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instOpFp(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instMadd(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instNmadd(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instMsub(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instNmsub(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instBranch(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t funct3 = DECODE_FUNCT3(inst);
  uint32_t rs1 = DECODE_RS1(inst);
  uint32_t rs2 = DECODE_RS2(inst);
  /* multiples of 2 */
  uint64_t offset = SIGN_EXTEND_64U((uint64_t) DECODE_IMM_B(inst), 12) << 1;
  bool branch = false;

  printf("offset = %ld\n", (int64_t) offset);

  switch(funct3) {
    case BRANCH_BEQ:
      branch = (c->reg[rs1] == c->reg[rs2]);
      break;
    case BRANCH_BNE:
      branch = (c->reg[rs1] != c->reg[rs2]);
      break;
    case BRANCH_BLT:
      branch = (((int64_t) c->reg[rs1]) < ((int64_t) c->reg[rs2]));
      break;
    case BRANCH_BGE:
      branch = (((int64_t) c->reg[rs1]) >= ((int64_t) c->reg[rs2]));
      break;
    case BRANCH_BLTU:
      branch = (c->reg[rs1] < c->reg[rs2]);
      break;
    case BRANCH_BGEU:
      branch = (c->reg[rs1] >= c->reg[rs2]);
      break;
    default:
      instUnsupported(inst, c, mem);
      break;
  }

  if(branch) {
    if(!ALIGNED(c->pc + offset, BASE_ALIGNMENT)) {
      fprintf(stderr, "misaligned instruction fetch exception: 0x%lx\n", c->pc + offset);

      exit(EXIT_FAILURE);
    }

    c->pc += offset;
  } else {
    c->pc += 4;
  }
}

void instJalr(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t rd = DECODE_RD(inst);
  uint32_t rs1 = DECODE_RS1(inst);
  uint64_t dest = c->reg[rs1] + SIGN_EXTEND_64U((uint64_t) DECODE_IMM_I(inst), 12); 
  /* zero out the LSB */
  dest &= UINT64_MAX - 1;

  if(!ALIGNED(dest, BASE_ALIGNMENT)) {
    fprintf(stderr, "misaligned instruction fetch exception: 0x%lx\n", dest);

    exit(EXIT_FAILURE);
  }

  /* LSB is zeroed out above */
  c->pc = dest;

  if(rd)
    c->reg[rd] = c->pc + 4;
}

void instJal(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t rd = DECODE_RD(inst);
  /* potentially very wrong */
  uint64_t offset = SIGN_EXTEND_64U((uint64_t) DECODE_IMM_J(inst), 20);

  /* 2 byte aligned */
  uint64_t dest = c->pc + offset + offset;

  if(!ALIGNED(dest, BASE_ALIGNMENT)) {
    fprintf(stderr, "misaligned instruction fetch exception: 0x%lx\n", dest);

    exit(EXIT_FAILURE);
  }

  c->pc = dest;
 
  printf("offset = 0x%lx\n", offset);

  if(rd)
    c->reg[rd] = c->pc + 4;
}

void instSystem(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

