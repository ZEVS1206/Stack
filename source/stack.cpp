#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"
#include "recalloc.h"
const Stack_Elem_t left_canary = 0xDEADA;
const Stack_Elem_t right_canary = 0xDEADC;

void stack_stop(Errors error, const char *file, int line)
{
    fprintf(stderr, "%s\nfile - %s\nline = %d\n", get_error(error), file, line);
    abort();
    return;
}

Errors stack_assert(struct MyStack *stack, const char *file, int line)
{
    Errors error = stack_check(stack);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\nfile - %s\nline = %d\n", get_error(error), file, line);
        abort();
    }
    return NO_ERRORS;
}

const char* get_error(Errors error)
{
    switch (error)
    {
        case ERROR_OF_ADD_TO_STACK:
            return "ERROR_OF_ADD_TO_STACK";
            break;
        case ERROR_OF_DEL_FROM_STACK:
            return "ERROR_OF_DEL_FROM_STACK";
            break;
        case ERROR_OF_NULL_SIZE:
            return "ERROR_OF_NULL_SIZE";
            break;
        case ERROR_OF_DESTRUCTOR_STACK:
            return "ERROR_OF_DESTRUCTOR_STACK";
            break;
        case ERROR_OF_CHECK_STACK:
            return "ERROR_OF_CHECK_STACK";
            break;
        case ERROR_OF_RECALLOC_STACK:
            return "ERROR_OF_RECALLOC_STACK";
            break;
        case ERROR_OF_STACK_OVERFLOW:
            return "ERROR_OF_STACK_OVERFLOW";
            break;
        case ERROR_OF_USING_DATA:
            return "ERROR_OF_USING_DATA";
            break;
        case NO_ERRORS:
            return "NO_ERRORS";
            break;
        default:
            return "UNKNOWN_TYPE_OF_ERROR";
            break;
    }
}

#ifdef DEBUG
Errors stack_constructor(struct MyStack *stack, int begin_capacity, const char *name, const char *file, int line)
#else
Errors stack_constructor(struct MyStack *stack, int begin_capacity)
#endif
{
    stack->data = (Stack_Elem_t *) calloc(begin_capacity + 2, sizeof(Stack_Elem_t));
    *(stack->data) = left_canary;
    stack->LEFT_CANARY = (const Stack_Elem_t)0xDEADA;
    *(stack->data + begin_capacity + 1) = right_canary;
    stack->RIGHT_CANARY = (const Stack_Elem_t)0xDEADC;
    stack->data = stack->data + 1;
    stack->size = 0;
    stack->capacity = begin_capacity;
    #ifdef DEBUG
    stack->name = name;
    stack->file = file;
    stack->line = line;
    #endif
    Errors error = STACK_ASSERT(stack);
    printf("|||||||||||\n");
    STACK_DUMP(stack);
    printf("|||||||||||\n");
    return error;
}

Errors stack_destructor(struct MyStack *stack)
{
    if (stack == NULL)
    {
        STACK_STOP(ERROR_OF_DESTRUCTOR_STACK);
    }
    if (stack->data == NULL)
    {
        STACK_STOP(ERROR_OF_DESTRUCTOR_STACK);
    }
    for (int i = 0; i < stack->size; i++)
    {
        (stack->data)[i] = 0;
    }

    stack->size = 0;
    stack->capacity = 0;
    // printf("|||||||||||\n");
    // stack_dump(stack);
    // printf("|||||||||||\n");
    free(stack->data - 1);
    return NO_ERRORS;
}


Errors do_recalloc(struct MyStack *stack, Stack_Elem_t *reserve, int old_capacity)
{
    Errors error = STACK_ASSERT(stack);
    reserve = stack->data;
    stack->data = (Stack_Elem_t *) recalloc((stack->data - 1), stack->capacity + 2, sizeof(Stack_Elem_t), old_capacity);
    if (stack->data == NULL)
    {
        stack->data = reserve;
        STACK_DUMP(stack);
        STACK_STOP(ERROR_OF_RECALLOC_STACK);
    }
    *(stack->data) = left_canary;
    *(stack->data + abs(stack->capacity + 2 - old_capacity)) = right_canary;
    stack->data = stack->data + 1;
    error = STACK_ASSERT(stack);
    return error;
}

Errors stack_check(const struct MyStack *stack)
{
    if (stack->data == NULL)
    {
        return ERROR_OF_USING_DATA;
    }
    if (stack->size > stack->capacity)
    {
        return ERROR_OF_RECALLOC_STACK;
    }
    if (stack->size < 0)
    {
        return ERROR_OF_NULL_SIZE;
    }
    return NO_ERRORS;
}

Errors stack_push(struct MyStack *stack, Stack_Elem_t element)
{
    Errors error = STACK_ASSERT(stack);
    (stack->data)[stack->size] = element;
    if (stack->size + 1 >= stack->capacity)
    {
        int old_capacity = stack->capacity;
        (stack->capacity) *= COEFFICIENT;
        Stack_Elem_t *reserve = NULL;
        error = do_recalloc(stack, reserve, old_capacity);
        if (error != NO_ERRORS)
        {
            STACK_DUMP(stack);
            STACK_STOP(ERROR_OF_ADD_TO_STACK);
        }
    }
    (stack->size)++;
    STACK_DUMP(stack);
    error = STACK_ASSERT(stack);
    return error;
}

Errors stack_pop(struct MyStack *stack, Stack_Elem_t *element)
{
    if (stack->size - 1 < 0)
    {
        STACK_STOP(ERROR_OF_NULL_SIZE);
    }
    Errors error = STACK_ASSERT(stack);
    *element = (stack->data)[stack->size - 1];
    printf("last_element=%lf\n\n", *element);
    (stack->data)[stack->size - 1] = 0;
    (stack->size)--;
    if ((stack->size + 2) % (COEFFICIENT) == 0)
    {
        int old_capacity = stack->capacity;
        stack->capacity /= COEFFICIENT;
        Stack_Elem_t *reserve = NULL;
        error = do_recalloc(stack, reserve, old_capacity);
        if (error != NO_ERRORS)
        {
            STACK_DUMP(stack);
            STACK_STOP(ERROR_OF_DEL_FROM_STACK);
        }
    }
    STACK_DUMP(stack);
    error = STACK_ASSERT(stack);
    return error;
}

#ifdef DEBUG
void stack_dump(struct MyStack *stack, const char *file, int line)
{
    printf("Information about stack:\n");
    printf("Stack address: %p\n", stack);
    if (stack != NULL)
    {
        printf("Name: %s\n", stack->name);
        printf("File: %s\n", file);
        printf("Line: %d\n", line);
        printf("Data address: %p\n", &(stack->data));
        printf("Size value: %d\n", stack->size);
        printf("Capacity value: %d\n", stack->capacity);
        printf("LEFT_CANARY: %lf\n", *(stack->data - 1));
        printf("RIGHT_CANARY: %lf\n", *(stack->data + stack->capacity));
        if (stack->data != NULL)
        {
            printf("Stack:\n");
            for (int i = 0; i < stack->capacity; i++)
            {
                printf("%lf ", (stack->data)[i]);
            }
        }
    }
    printf("\n\n");
    return;
}
#else
void stack_dump(struct MyStack *stack)
{
    printf("Information about stack:\n");
    //printf("Stack address: %p\n", stack);
    if (stack != NULL)
    {
        //printf("Name: %s\n", stack->name);
        //printf("File: %s\n", file);
        //printf("Line: %d\n", line);
        //printf("Data address: %p\n", &(stack->data));
        printf("Size value: %d\n", stack->size);
        printf("Capacity value: %d\n", stack->capacity);
        if (stack->data != NULL)
        {
            printf("Stack:\n");
            for (int i = 0; i < stack->capacity; i++)
            {
                printf("%lf ", (stack->data)[i]);
            }
        }
    }
    printf("\n\n");
    return;
}
#endif
