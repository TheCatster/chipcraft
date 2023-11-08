//
// Created by Daniil Rose on 10/23/23.
//

#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "../include/log.h"

#define MEMORY_SIZE 4096
#define V_REGISTERS_SIZE 16
#define STACK_SIZE 16
#define KEYPAD_SIZE 16
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

typedef struct {
    int top;
    int array[STACK_SIZE];
    int size;
} STACK;

/*
 * STACK Associated Methods
 */
STACK *stack_new(void);

bool stack_push(STACK *stack, uint8_t input);

bool stack_pop(STACK *stack, uint8_t *popped);

bool stack_show(STACK *stack, uint8_t *contents);

typedef struct {
    // CPU registers (V0 - VF)
    uint8_t V[V_REGISTERS_SIZE];

    // Index register
    uint16_t I;

    // Program counter
    uint16_t PC;

    // Stack
    STACK *stack;
    uint8_t SP;

    // Memory (4 KB)
    uint8_t memory[MEMORY_SIZE];

    // Timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    // Input
    bool keypad[KEYPAD_SIZE];
    uint16_t keymap[KEYPAD_SIZE][2];

    // Display (64x32)
    bool display[DISPLAY_WIDTH][DISPLAY_HEIGHT];
} CHIP8;

/*
 * CHIP-8 Associated Methods
 */
CHIP8 *chip8_new(void);

void chip8_run(char *file_name);

void chip8_load_fonts(CHIP8 *emulator);

void chip8_load_keymap(CHIP8 *emulator);

bool chip8_load_rom(CHIP8 *emulator, char *file_name);

uint16_t chip8_fetch(CHIP8 *emulator);

bool chip8_decode_execute(CHIP8 *emulator, uint16_t instruction);

void chip8_draw(CHIP8 *emulator);
