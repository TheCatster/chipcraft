//
// Created by Daniil Rose on 10/23/23.
//

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define MEMORY_SIZE 4096
#define V_REGISTERS_SIZE 16
#define STACK_SIZE 16
#define KEYPAD_SIZE 16
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

typedef struct {
    // CPU registers (V0 - VF)
    uint8_t V[V_REGISTERS_SIZE];

    // Index register
    uint16_t I;

    // Program counter
    uint16_t PC;

    // Stack
    uint16_t stack[STACK_SIZE];
    uint8_t SP;

    // Memory (4 KB)
    uint8_t memory[MEMORY_SIZE];

    // Timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    // Input
    bool keypad[KEYPAD_SIZE];

    // Display (64x32)
    bool display[DISPLAY_WIDTH][DISPLAY_HEIGHT];
} CHIP8;

/*
 * CHIP-8 Associated Methods
*/
void chip8_load_fonts(CHIP8 *emulator);


