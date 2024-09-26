#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "stack_functions.h"

int main(){
    struct MyStack stack = {0};
    Errors error = NO_ERRORS;
    error = stack_constructor(&stack, 10);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\n", get_error(error));
        return -1;
    }
    error = stack_push(&stack, 100);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\n", get_error(error));
        return -1;
    }
    error = stack_push(&stack, 200);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\n", get_error(error));
        return -1;
    }
    Stack_Elem_t last_element = 0;
    error = stack_pop(&stack, &last_element);
    printf("last_element=%lf\n\n", last_element);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\n", get_error(error));
        return -1;
    }
    error = stack_pop(&stack, &last_element);
    printf("last_element=%lf\n\n", last_element);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\n", get_error(error));
        return -1;
    }
    error = stack_destructor(&stack);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "%s\n", get_error(error));
        return -1;
    }
    return 0;
}


Errors stack_constructor(struct MyStack *stack, int begin_capacity)
{
    stack->data = (Stack_Elem_t *) calloc(begin_capacity, sizeof(Stack_Elem_t));
    stack->size = 0;
    stack->capacity = begin_capacity;
    Errors error = NO_ERRORS;
    error = stack_check(stack);
    printf("|||||||||||\n");
    stack_dump(stack);
    printf("|||||||||||\n");
    return error;
}

Errors stack_destructor(struct MyStack *stack)
{
    if (stack == NULL)
    {
        return ERROR_OF_DESTRUCTOR_STACK;
    }
    for (int i = 0; i < stack->size; i++)
    {
        (stack->data)[i] = 0;
    }
    if (stack->data == NULL)
    {
        return ERROR_OF_DESTRUCTOR_STACK;
    }

    stack->size = 0;
    stack->capacity = 0;
    // printf("|||||||||||\n");
    // stack_dump(stack);
    // printf("|||||||||||\n");
    free(stack->data);
    return NO_ERRORS;
}

