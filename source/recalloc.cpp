#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "recalloc.h"

void* recalloc(Stack_Elem_t *pointer, int new_size, size_t size_of_type, int old_size)
{
    Stack_Elem_t *ptr =(Stack_Elem_t *) realloc(pointer, new_size * size_of_type);
    int fill_bytes = (new_size > old_size) ? new_size - old_size : new_size;
    memset(ptr, 0, fill_bytes);
    return ptr;
}
