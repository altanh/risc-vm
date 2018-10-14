#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "mem.h"

bool memAlloc(mem_t *m, size_t n) {
  m->size = n;
  m->bytes = (uint8_t*) malloc(n * sizeof(uint8_t));

  if(!m->bytes)
    return false;

  return true;
}

int memRead(mem_t *m, size_t index, size_t n, uint8_t *dest) {
  assert(m != NULL);
  assert(index + n <= m->size);

  uint8_t *byte_ptr = m->bytes;
  while(n-- > 0)
    *dest++ = *(index + byte_ptr++);

  return 1;
}

int memWrite(mem_t *m, size_t index, size_t n, uint8_t *src) {
  assert(m != NULL);
  assert(index + n <= m->size);

  uint8_t *byte_ptr = m->bytes;
  while(n-- > 0)
    *(index + byte_ptr++) = *src++;

  return 1;
}

void memDump(mem_t *m) {
  size_t i;
  for(i = 0; i < m->size; i += 32) {
    printf("0x%08lx:", i);
    
    size_t j;
    for(j = i; j < i + 32; ++j)
      printf(" %02x", m->bytes[j]);

    printf("\n");
  }

  if(m->size % 32) {
    printf("0x%08lx:", 32 * (m->size / 32));
    
    for(i = 32 * (m->size / 32); i < m->size; ++i)
      printf(" %02x", m->bytes[i]);

    printf("\n");
  }
}

