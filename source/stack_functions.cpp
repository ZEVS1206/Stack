#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "stack_functions.h"

static void* recalloc(Stack_Elem_t *pointer, int new_size, size_t size_of_type, int old_size);

const char* get_error(Errors error)
{
    switch (error)
    {
        case -6:
            return "ERROR_OF_NULL_SIZE";
            break;
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

static void* recalloc(Stack_Elem_t *pointer, int new_size, size_t size_of_type, int old_size)
{
    Stack_Elem_t *ptr =(Stack_Elem_t *) realloc(pointer, new_size * size_of_type);
    if (new_size < old_size)
    {
        for (int i = 0; i < new_size; i++)
        {
            ptr[i] = 0;
        }
    } else
    {
        for (int i = old_size; i < new_size; i++)
        {
            ptr[i] = 0;
        }
    }
    return (void *) ptr;
}

Errors stack_check(struct MyStack *stack)
{
    if (stack->data == NULL)
    {
        return ERROR_OF_CREATING_DATA;
    }
    if (stack->size > stack->capacity)
    {
        return ERROR_OF_RECALLOC_STACK;
    }
    return NO_ERRORS;
}

Errors stack_push(struct MyStack *stack, Stack_Elem_t element)
{
    (stack->data)[stack->size] = element;
    if (stack->size + 1 > stack->capacity)
    {
        (stack->capacity) *= COEFFICIENT;
        stack->data = (Stack_Elem_t *) recalloc((stack->data), stack->capacity, sizeof(Stack_Elem_t), stack->size);
    }
    (stack->size)++;
    Errors error = stack_check(stack);
    stack_dump(stack);
    return error;
}

Errors stack_pop(struct MyStack *stack, Stack_Elem_t *element)
{
    if (stack->size - 1 < 0)
    {
        return ERROR_OF_NULL_SIZE;
    }
    *element = (stack->data)[stack->size - 1];
    (stack->data)[stack->size - 1] = 0;
    (stack->size)--;
    if ((stack->size - 1) % (stack->capacity) == 0)
    {
        stack->capacity /= COEFFICIENT;
        stack->data = (Stack_Elem_t *) recalloc((stack->data), stack->capacity, sizeof(Stack_Elem_t), stack->size);
    }
    Errors error = stack_check(stack);
    stack_dump(stack);
    return error;
}

void stack_dump(struct MyStack *stack)
{
    printf("Information about stack:\n");
    printf("Stack address: %p\n", stack);
    printf("Data address: %p\n", &(stack->data));
    printf("Size value: %d\n", stack->size);
    printf("Capacity value: %d\n", stack->capacity);
    printf("Stack:\n");
    for (int i = 0; i < stack->capacity; i++)
    {
        printf("%lf ", (stack->data)[i]);
    }
    printf("\n\n");
    return;
}

