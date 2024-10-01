#ifndef STACK_H
#define STACK_H

#include <stdarg.h>
#define COEFFICIENT 2
#define DEBUG
#define STACK_ASSERT(stack) stack_assert((stack), __FILE__, __LINE__)
#define STACK_STOP(error) stack_stop((error), __FILE__, __LINE__)


#ifdef DEBUG
    #define STACK_CTOR(stack, begin_capacity) stack_constructor((stack), (begin_capacity), #stack, __FILE__, __LINE__)
    #define STACK_DUMP(stack) stack_dump((stack), __FILE__, __LINE__)
#else
    #define STACK_CTOR(stack, begin_capacity) stack_constructor((stack), (begin_capacity))
    #define STACK_DUMP(stack) stack_dump((stack))
#endif

typedef double Stack_Elem_t;


enum Errors
{
    ERROR_OF_ADD_TO_STACK      = -8,
    ERROR_OF_DEL_FROM_STACK    = -7,
    ERROR_OF_NULL_SIZE         = -6,
    ERROR_OF_DESTRUCTOR_STACK  = -5,
    ERROR_OF_CHECK_STACK       = -4,
    ERROR_OF_RECALLOC_STACK    = -3,
    ERROR_OF_STACK_OVERFLOW    = -2,
    ERROR_OF_USING_DATA        = -1,
    NO_ERRORS                  =  0
};

struct MyStack
{
    #ifdef DEBUG
    const char *name;
    const char *file;
    int line;
    #endif
    Stack_Elem_t LEFT_CANARY;
    Stack_Elem_t RIGHT_CANARY;
    Stack_Elem_t *data;
    int size;
    int capacity;
};

#ifdef DEBUG
    Errors stack_constructor(struct MyStack *stack, int begin_capacity, const char *name, const char *file, int line);
    void stack_dump(struct MyStack *stack, const char *file, int line);
#else
    Errors stack_constructor(struct MyStack *stack, int begin_capacity);
    void stack_dump(struct MyStack *stack);
#endif
Errors stack_destructor(struct MyStack *stack);



Errors stack_check(const struct MyStack *stack);
Errors stack_push(struct MyStack *stack, Stack_Elem_t element);
Errors stack_pop(struct MyStack *stack, Stack_Elem_t *element);
Errors do_recalloc(struct MyStack *stack, Stack_Elem_t *reserve, int old_capacity);
Errors stack_assert(struct MyStack *stack, const char *file, int line);
void stack_stop(Errors error, const char *file, int line);
const char *get_error(Errors error);
#endif
