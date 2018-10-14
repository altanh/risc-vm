#ifndef _RISC_VM_UTIL_H_
#define _RISC_VM_UTIL_H_

#include <stdint.h>

/* extract bits x[start] to x[start + 1] */
#define EXTRACT(x, start, n) (((x) & (((1 << (n)) - 1) << (start))) >> (start))
#define ALIGNED(ptr, align) (!((ptr) & ((align) - 1)))

/* w is (pseudo) bitwidth of x */
#define SIGN_EXTEND_64U(x, w) ((((x) & (1 << ((w) - 1))) ? (UINT64_MAX << (w)) : 0x0) | (x))

#endif
