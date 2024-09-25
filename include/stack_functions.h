#ifndef STACK_F_H
#define STACK_F_H
#include "stack.h"

Errors stack_check(struct MyStack *stack);
Errors stack_constructor(struct MyStack *stack, int begin_capacity);
Errors stack_push(struct MyStack *stack, Stack_Elem_t element);
Errors stack_pop(struct MyStack *stack);
Errors stack_dump(struct MyStack *stack);
Errors stack_assert(struct MyStack *stack);
const char *get_error(Errors error);
#endif
