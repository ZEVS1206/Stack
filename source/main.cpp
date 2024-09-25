#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(){
    struct MyStack stack = {0};
    Errors error = NO_ERRORS;
    error = stack_constructor(&stack, 10);
    if (error != NO_ERRORS)
    {
        fprintf("%s\n", get_error(error), stderr);
        return -1;
    }
    error = stack_push(&stack, 100);
    if (error != NO_ERRORS)
    {
        fprintf("%s\n", get_error(error), stderr);
        return -1;
    }
    error = stack_dump(&stack);
    if (error != NO_ERRORS)
    {
        fprintf("%s\n", get_error(error), stderr);
        return -1;
    }
    error = stack_pop(&stack);
    if (error != NO_ERRORS)
    {
        fprintf("%s\n", get_error(error), stderr);
        return -1;
    }
    error = stack_dump(&stack);
    if (error != NO_ERRORS)
    {
        fprintf("%s\n", get_error(error), stderr);
        return -1;
    }
    error = stack_destructor(&stack);
    if (error != NO_ERRORS)
    {
        fprintf("%s\n", get_error(error), stderr);
        return -1;
    }
    return 0;
}
