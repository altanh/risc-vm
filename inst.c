#include <stdio.h>

#include "inst.h"
#include "util.h"
#include "cpu.h"
#include "mem.h"

#define LOAD_LB 0x0
#define LOAD_LH 0x1
#define LOAD_LW 0x2
#define LOAD_LD 0x3
#define LOAD_LBU 0x4
#define LOAD_LHU 0x5
#define LOAD_LWU 0x6

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

void instUnsupported(uint32_t inst, cpu_t *c, mem_t *mem) {
  fprintf(stderr, "error: unsupported instruction 0x%032x\n", inst);
}

void instLoad(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t funct3 = EXTRACT(inst, 12, 3);
  uint32_t rd = EXTRACT(inst, 7, 5);
  uint32_t rs1 = EXTRACT(inst, 15, 5);
  int64_t offset = (int64_t) EXTRACT(inst, 20, 12);

  uint32_t w;
  uint16_t h;
  uint8_t b;

  /* need to see if sign extension works like I think it does */
  switch(funct3) {
    case LOAD_LB:
      memRead(mem, c->reg[rs1] + offset, 1, &b);
      c->reg[rd] = (int8_t) b;
      break;
    case LOAD_LH:
      memRead(mem, c->reg[rs1] + offset, 2, (uint8_t*) &h);
      c->reg[rd] = (int16_t) h;
      break;
    case LOAD_LW:
      memRead(mem, c->reg[rs1] + offset, 4, (uint8_t*) &w);
      c->reg[rd] = (int32_t) w;
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
  uint32_t op = (EXTRACT(inst, 25, 7) << 3) | (EXTRACT(inst, 12, 3));
  uint32_t rd = EXTRACT(inst, 7, 5);
  uint32_t rs1 = EXTRACT(inst, 15, 5);
  uint32_t rs2 = EXTRACT(inst, 20, 5);

  switch(op) {
    case OP_ADD:
      c->reg[rd] = c->reg[rs1] + c->reg[rs2];
      break;
    case OP_SUB:
      c->reg[rd] = c->reg[rs1] + (~c->reg[rs2] + 1);
      break;
    case OP_SLL:
      c->reg[rd] = c->reg[rs1] << EXTRACT(c->reg[rs2], 0, 5);
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
      c->reg[rd] = c->reg[rs1] >> EXTRACT(c->reg[rs2], 0, 5);
      break;
    case OP_SRA:
      c->reg[rd] = (uint64_t) (((int64_t) c->reg[rs1]) >> EXTRACT(c->reg[rs2], 0, 5));
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
  printf("MADD\n");
  instUnsupported(inst, c, mem);
}

void instNmadd(uint32_t inst, cpu_t *c, mem_t *mem) {
  printf("NMADD\n");
  instUnsupported(inst, c, mem);
}

void instMsub(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instNmsub(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instBranch(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

void instJalr(uint32_t inst, cpu_t *c, mem_t *mem) {
  
}

void instJal(uint32_t inst, cpu_t *c, mem_t *mem) {
  uint32_t rd = EXTRACT(inst, 7, 5);
  uint64_t offset = (EXTRACT(inst, 31, 1) ? 0xFFFFFFFFFF000000 : 0x0) |
                    (EXTRACT(inst, 12, 8) << 0XB) |
                    (EXTRACT(inst, 20, 1) << 0xA) |
                    EXTRACT(inst, 21, 10);

  c->pc += offset + offset;
  
  if(rd)
    c->reg[rd] = c->pc + 4;
}

void instSystem(uint32_t inst, cpu_t *c, mem_t *mem) {
  instUnsupported(inst, c, mem);
}

