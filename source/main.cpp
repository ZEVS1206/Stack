#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(){
    struct MyStack stack = {0};
    Errors error = NO_ERRORS;
    error = STACK_CTOR(&stack, 2);
    error = stack_push(&stack, 300);
    for (int i = 0; i < 50; i++)
    {        
        error = stack_push(&stack, i + 1);
    }
    Stack_Elem_t last_element = 0;
    for (int i = 0; i < 40; i++)
    {

        error = stack_pop(&stack, &last_element);
    }
    error = stack_destructor(&stack);
    printf("%s\n", get_error(error));
    return 0;
}


