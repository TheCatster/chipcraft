//
// Created by Daniil Rose on 11/8/23.
//

#include <assert.h>
#include <stdlib.h>
#include "../include/chip8.h"

int main(void) {
  STACK* stack = stack_new();
  uint16_t value;
  bool result;

  // Prepare the stack by pushing values.
  for (uint16_t i = 0; i < STACK_SIZE; ++i) {
    stack_push(stack, i);
  }

  // Test popping values from the stack.
  for (uint16_t i = STACK_SIZE; i > 0; --i) {
    result = stack_pop(stack, &value);
    assert(result);
    assert(value == i - 1);
  }

  // Stack should be empty now.
  result = stack_pop(stack, &value);
  assert(!result);  // Popping from an empty stack should fail.

  return 0;  // Success
}
