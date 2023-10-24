//
// Created by Daniil Rose on 10/23/23.
//

#include "chip8.h"

bool push(STACK *stack, uint8_t input) {
    if (stack->top == stack->size - 1) {
        return false;
    } else {
        stack->top = stack->top + 1;
        stack->array[stack->top] = input;

        return true;
    }
}

bool pop(STACK *stack, uint8_t *popped) {
    if (stack->top == -1) {
        return false;
    } else {
        *popped = stack->array[stack->top];
        stack->top = stack->top - 1;

        return true;
    }
}

bool show(STACK *stack, uint8_t *contents) {
    if (stack->top == -1) {
        return false;
    } else {
        for (int i = stack->top; i >= 0; --i) {
            contents[i] = stack->array[i];
        }

        return true;
    }
}

/*
 * Load the CHIP-8 fonts into the expected location in RAM
 */
void chip8_load_fonts(CHIP8 *emulator) {
    uint8_t fonts[80] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0,     // 0
            0x20, 0x60, 0x20, 0x20, 0x70,     // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
            0x90, 0x90, 0xF0, 0x10, 0x10, // 4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
            0xF0, 0x10, 0x20, 0x40, 0x40, // 7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
            0xF0, 0x90, 0xF0, 0x90, 0x90, // A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
            0xF0, 0x80, 0x80, 0x80, 0xF0, // C
            0xE0, 0x90, 0x90, 0x90, 0xE0, // D
            0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
            0xF0, 0x80, 0xF0, 0x80, 0x80   // F
    };

    memcpy(emulator->memory + 0x50, fonts, 80);
}
