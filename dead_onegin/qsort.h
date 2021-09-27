#ifndef _QSORT_H_
#define _QSORT_H_

#include <stdlib.h>

//*************************************************************************************************

void swapv     (void *e1,       void *e2,     size_t esize);
void qsort_my  (void *array,    size_t asize, size_t esize, int (*scmp) (const void *, const void *));

#endif
