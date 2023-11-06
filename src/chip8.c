//
// Created by Daniil Rose on 10/23/23.
//

#include "../include/chip8.h"

/*
 * Creates a new stack instance
 */

/**
 * @brief Create a new stack
 * @return a pointer to the stack
 */
STACK *stack_new(void) {
    static STACK stack = {0};
    stack.top = -1;
    stack.size = STACK_SIZE;

    return &stack;
}

/*
 * Basic operations for the stack
 */

/**
 * @brief Push onto the stack
 * @param stack: a pointer to the stack
 * @param input: the value to push onto the stack
 * @return a boolean that indicates success
 */
bool stack_push(STACK *stack, uint8_t input) {
    if (stack->top == stack->size - 1) {
        return false;
    } else {
        stack->top = stack->top + 1;
        stack->array[stack->top] = input;

        return true;
    }
}

/**
 * @brief Pop the stack
 * @param stack: a pointer to the stack
 * @param popped: a pointer to the number that was popped
 * @return a boolean that indicates success
 */
bool stack_pop(STACK *stack, uint8_t *popped) {
    if (stack->top == -1) {
        return false;
    } else {
        *popped = stack->array[stack->top];
        stack->top = stack->top - 1;

        return true;
    }
}

/**
 * @brief Show the contents of the stack
 * @param stack: pointer to the stack
 * @param contents: the array containing the contents of the stack
 * @return a boolean that indicates success
 */
bool stack_show(STACK *stack, uint8_t *contents) {
    if (stack->top == -1) {
        return false;
    } else {
        for (int i = stack->top; i >= 0; --i) {
            contents[i] = stack->array[i];
        }

        return true;
    }
}

/**
 * @brief Creates a new static CHIP-8 instance
 * @param void
 * @returns a pointer to the CHIP-8 emulator
 */
CHIP8 *chip8_new(void) {
    static CHIP8 emulator = {0};
    chip8_load_fonts(&emulator);
    chip8_load_keymap(&emulator);
    emulator.PC = 0x200;
    emulator.stack = stack_new();

    return &emulator;
}

/**
 * @brief The main entrypoint for the emulator
 * @param file_name: the name of the ROM file
 * @returns void
 */
void chip8_run(char *file_name) {
    CHIP8 *emulator = chip8_new();

    bool load = chip8_load_rom(emulator, file_name);
    if (load == false) {
        perror("ROM was not loaded successfully!");
        return;
    }

    // For testing
    uint8_t counter = 0;

    while (true) {
        uint16_t instruction = chip8_fetch(emulator);
        bool success = chip8_decode_execute(emulator, instruction);
        counter++;

        if (counter == 5) {
            break;
        }
    }
}

/**
 * @brief Load the CHIP-8 fonts into the expected location in RAM
 * @param emulator: a pointer to the CHIP-8 emulator
 * @returns void
 */
void chip8_load_fonts(CHIP8 *emulator) {
    uint8_t fonts[80] = {
            0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
            0x20, 0x60, 0x20, 0x20, 0x70, // 1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
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
            0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
            0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    memcpy(emulator->memory + 0x50, fonts, 80);
}

/**
 * @brief Load the CHIP-8 keymap into the struct
 * @param emulator: a pointer to the CHIP-8 emulator
 * @returns void
 */
void chip8_load_keymap(CHIP8 *emulator) {
    uint16_t keymap[KEYPAD_SIZE][2] = {
            {SDL_SCANCODE_1, 0x1},
            {SDL_SCANCODE_2, 0x2},
            {SDL_SCANCODE_3, 0x3},
            {SDL_SCANCODE_4, 0xC},
            {SDL_SCANCODE_Q, 0x4},
            {SDL_SCANCODE_W, 0x5},
            {SDL_SCANCODE_E, 0x6},
            {SDL_SCANCODE_R, 0xD},
            {SDL_SCANCODE_A, 0x7},
            {SDL_SCANCODE_S, 0x8},
            {SDL_SCANCODE_D, 0x9},
            {SDL_SCANCODE_F, 0xE},
            {SDL_SCANCODE_Z, 0xA},
            {SDL_SCANCODE_X, 0x0},
            {SDL_SCANCODE_C, 0xB},
            {SDL_SCANCODE_V, 0xF},
    };

    memcpy(emulator->keymap, keymap, KEYPAD_SIZE);
}

/**
 * @brief Load a ROM into the emulator's memory
 * @param emulator: a pointer to the CHIP-8 emulator
 * @param filename: the name of the ROM file
 * @returns a boolean indicating success
 */
bool chip8_load_rom(CHIP8 *emulator, char *file_name) {
    printf("Loading ROM\n");

    FILE *fp = fopen(file_name, "rb");

    if (fp == NULL) {
        return false;
    }

    struct stat st = {0};
    stat(file_name, &st);
    size_t f_size = st.st_size;

    size_t bytes_read = fread(emulator->memory + 0x200, 1, sizeof(emulator->memory) - 0x200, fp);

    fclose(fp);

    if (bytes_read != f_size) {
        return false;
    }

    printf("Bytes read: %zu\n", bytes_read);

    return true;
}

/**
 * @brief Fetch the next instruction
 * @param emulator: a pointer to the CHIP-8 emulator
 * @returns a CHIP-8 instruction
 */
uint16_t chip8_fetch(CHIP8 *emulator) {
    uint16_t instruction = emulator->memory[emulator->PC] + emulator->memory[emulator->PC + 1];
    emulator->PC += 2;

    printf("Instruction is: 0x%04X\n", instruction);
    printf("PC is: 0x%04X\n", emulator->PC);

    return instruction;
}

/**
 * @brief Decodes the instruction
 * @param emulator: a pointer to the CHIP-8 emulator
 * @param instruction: the instruction to decode and execute
 * @returns a boolean that indicates success
 */
bool chip8_decode_execute(CHIP8 *emulator, uint16_t instruction) {
    uint16_t category = (instruction & 0xF000) >> 12;
    uint16_t x = (instruction & 0x0F00) >> 8;
    uint16_t y = (instruction & 0x00F0) >> 4;
    uint16_t n = (instruction & 0x000F);
    uint16_t nn = (y << 4) | n;
    uint32_t nnn = (x << 8) | (y << 4) | n;

    switch (category) {
        case 0x0:
            switch (nnn) {
                // 00E0: Clears the screen
                case 0x0E0:
                    printf("0x00E0 - Clearing screen\n");
                    for (size_t i = 0; i < DISPLAY_HEIGHT; i++) {
                        for (size_t j = 0; j < DISPLAY_WIDTH; j++) {
                            emulator->display[j][i] = false;
                        }
                    }
                    break;
                default:
                    printf("0x0%03X - Unknown instruction\n", nnn);
                    return false;
            }
            break;
        case 0x1: // 1NNN - Jump
            return false;
        case 0x6: // 6XNN - Set register VX
            return false;
        case 0x7: // 7XNN - Add value to register VX
            return false;
        case 0xA: // ANNN - Set index register I
            return false;
        case 0xD: // DXYN - Display/draw
            return false;
        default:
            return false;
    }

    // For the sake of testing, always quit after one loop.
    return false;
}

