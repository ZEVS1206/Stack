#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(){
    struct MyStack stack = {0};
    Errors error = NO_ERRORS;
    error = STACK_CTOR(&stack, 2);
    // error = stack_push(&stack, 100);
    // error = stack_push(&stack, 200);
    // // int d[3] = {0};
    // // for (int i = 0; i < 4; i++)
    // // {
    // //     d[i] = 0;
    // //     printf("%p\n", &(d[i]));
    // // }
    // Stack_Elem_t last_element = 0;
    // error = stack_pop(&stack, &last_element);
    // error = stack_pop(&stack, &last_element);
    // error = stack_destructor(&stack);
    // error = STACK_CTOR(&stack, 2);
    // error = stack_push(&stack, 300);
    // error = stack_destructor(&stack);
    // printf("%s\n", get_error(error));
    for (int i = 0; i < 50; i++)
    {
        //printf("stack hash before push=%lu\n", stack.hash_result);
        error = stack_push(&stack, i + 1);
<<<<<<< Updated upstream
        stack.data[stack.size - 1] = 6346;
        printf("stack_hash=%u\n", stack.hash_result);
=======

        //first vulnerability
        //error = stack_destructor(&stack);
        //error = STACK_CTOR(&stack, 2);

        //second vulnerability
        //stack.data[stack.size - 1] = 13;
        //stack.hash_result = hash(&stack, stack.capacity);
        //printf("stack_hash after push=%lu\n", stack.hash_result);
>>>>>>> Stashed changes
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


