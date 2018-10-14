#ifndef _RISC_VM_UTIL_H_
#define _RISC_VM_UTIL_H_

#define EXTRACT(x, start, n) (((x) & (((1 << (n)) - 1) << (start))) >> (start))
#define ALIGNED(ptr, align) (!((ptr) & ((align) - 1)))

#endif
