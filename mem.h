#ifndef _RISC_VM_MEM_H_
#define _RISC_VM_MEM_H_

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h> /* size_t */

typedef struct {
  size_t size; /* in bytes */
  uint8_t *bytes;
} mem_t;

bool memAlloc(mem_t *m, size_t n);

int memRead(mem_t *m, size_t index, size_t n, uint8_t *dest);
int memWrite(mem_t *m, size_t index, size_t n, uint8_t *src);

void memDump(mem_t *m);

#endif
