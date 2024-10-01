#ifndef recalloc_h
#define recalloc_h

#include "stack.h"

void* recalloc(Stack_Elem_t *pointer, int new_size, size_t size_of_type, int old_size);

#endif
