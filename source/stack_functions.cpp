#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "stack_functions.h"

const char* get_error(Errors error)
{
    switch (error)
    {
        case -5:
            return "ERROR_OF_DESTRUCTOR_STACK";
            break;
        case -4:
            return "ERROR_OF_CHECK_STACK";
            break;
        case -3:
            return "ERROR_OF_RECALLOC_STACK";
            break;
        case -2:
            return "ERROR_OF_STACK_OVERFLOW";
            break;
        case -1:
            return "ERROR_OF_CREATING_DATA";
            break;
        case 0:
            return "NO_ERRORS";
            break;
        default:
            return "UNKNOWN_TYPE_OF_ERROR";
            break;
    }
}

Errors stack_constructor(struct MyStack *stack, int begin_capacity)
{
    stack->data = (Stack_Elem_t *) calloc(begin_capacity, sizeof(Stack_Elem_t));
    stack->size = 0;
    stack->capacity = begin_capacity;
    Errors error = NO_ERRORS;
    error = stack_check(&stack);
    return error;
}

Errors stack_check(struct MyStack *stack)
{
    if (stack->data == NULL)
    {
        return ERROR_OF_CREATING_DATA;
    }
    if (stack->size > stack->capacity)
    {
        return ERROR_OF_REALLOC_STACK;
    }
    return NO_ERRORS;
}
Errors stack_push(struct MyStack *stack, Stack_Elem_t element)
{
    stack->data[size] = element;
    size++;
    if (size >
