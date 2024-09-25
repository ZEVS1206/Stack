#ifndef STACK_H
#define STACK_H
typedef Stack_Elem_t double;

enum Errors
{
    ERROR_OF_DESTRUCTOR_STACK  = -5,
    ERROR_OF_CHECK_STACK       = -4,
    ERROR_OF_RECALLOC_STACK    = -3,
    ERROR_OF_STACK_OVERFLOW    = -2,
    ERROR_OF_CREATING_DATA     = -1,
    NO_ERRORS                  = 0
};

struct MyStack
{
    Stack_Elem_t *data;
    int size;
    int capacity;
};

Error stack_constructor(struct MyStack *stack, int begin_capacity);
Error stack_destructor(struct MyStack *stack);


#endif
