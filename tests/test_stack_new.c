//
// Created by Daniil Rose on 11/8/23.
//

#include "../include/chip8.h"
#include <assert.h>
#include <stdlib.h>

int main() {
    STACK *stack = stack_new();
    assert(stack != NULL);
    assert(stack->top == -1);
    assert(stack->size == STACK_SIZE);
    
    return 0; // Success
}
