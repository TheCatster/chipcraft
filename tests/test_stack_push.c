//
// Created by Daniil Rose on 11/8/23.
//

#include "../include/chip8.h"
#include <assert.h>
#include <stdlib.h>

int main() {
    STACK *stack = stack_new();
    bool result;

    // Test pushing values onto the stack.
    for (uint16_t i = 0; i < STACK_SIZE; ++i) {
        result = stack_push(stack, i);
        assert(result);
        assert(stack->array[stack->top] == i);
    }

    // Stack should be full now.
    result = stack_push(stack, 0xFFFF);
    assert(!result); // Pushing to a full stack should fail.
    
    return 0; // Success
}
