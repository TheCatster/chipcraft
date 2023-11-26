//
// Created by Daniil Rose on 11/8/23.
//

#include <assert.h>
#include <stdlib.h>
#include "../include/chip8.h"

int main(void) {
  STACK* stack = stack_new();
  assert(stack != NULL);
  assert(stack->top == -1);
  assert(stack->size == STACK_SIZE);

  return 0;  // Success
}
