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
    size_t counter = 0;

    while (true) {
        uint16_t instruction = chip8_fetch(emulator);
        bool success = chip8_decode_execute(emulator, instruction);
        if (success == false || counter == 25) {
            break;
        }

        counter++;
    }
}

/**
 * @brief Load the CHIP-8 fonts into the expected location in RAM
 * @param emulator: a pointer to the CHIP-8 emulator
 * @returns void
 */
void chip8_load_fonts(CHIP8 *emulator) {
    uint8_t fonts[80] = {0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
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
    uint16_t keymap[KEYPAD_SIZE][2] = {{SDL_SCANCODE_1, 0x1},
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
                                       {SDL_SCANCODE_V, 0xF},};

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
    uint16_t instruction = emulator->memory[emulator->PC] << 8 | emulator->memory[emulator->PC + 1];
    emulator->PC += 2;

    return instruction;
}

/**
 * @brief Decodes the instruction
 * @param emulator: a pointer to the CHIP-8 emulator
 * @param instruction: the instruction to decode and execute
 * @returns a boolean that indicates success
 */
bool chip8_decode_execute(CHIP8 *emulator, uint16_t instruction) {
    uint8_t category = (instruction & 0xF000) >> 12;
    uint8_t x = (instruction & 0x0F00) >> 8;
    uint8_t y = (instruction & 0x00F0) >> 4;
    uint8_t n = (instruction & 0x000F);
    uint16_t nn = (y << 4) | n;
    uint32_t nnn = (x << 8) | (y << 4) | n;

    switch (category) {
        case 0x0:
            switch (nnn) {
                case 0x0E0: // 00E0: Clears the screen
                    printf("0x00E0 - Clearing screen\n");
                    for (size_t i = 0; i < DISPLAY_HEIGHT; i++) {
                        for (size_t j = 0; j < DISPLAY_WIDTH; j++) {
                            emulator->display[j][i] = false;
                        }
                    }
                    break;
                case 0x0EE:; // 00EE: Return from subroutine
                    printf("0x00EE - Returning from subroutine\n");
                    uint8_t pc = 0;

                    bool pop_res = stack_pop(emulator->stack, &pc);
                    if (pop_res == false) {
                        return false;
                    }

                    emulator->PC = pc;
                    break;
                default:
                    // This case doesn't matter for modern CHIP-8 emulators
                    printf("0x%04X - Unnecessary instruction\n", instruction);
                    break;
            }
            break;
        case 0x1: // 1NNN: Jump
            printf("0x1NNN - Jumping to 0x%04X\n", nnn);
            emulator->PC = nnn;
            break;
        case 0x2:; // 0x2NNN: Call a subroutine
            printf("0x2NNN - Calling a subroutine\n");
            bool push_res = stack_push(emulator->stack, emulator->PC);
            if (push_res == false) {
                return false;
            }

            emulator->PC = nnn;
            break;
        case 0x3: // 0x3XNN: Skip if VX equals NN
            printf("0x3XNN - Skipping if VX equals NN\n");
            if (emulator->V[x] == nn) {
                emulator->PC += 2;
            }
            break;
        case 0x4: // 0x4XNN: Skip if VX does not equal NN
            printf("0x4XNN - Skipping if VX does not equal NN\n");
            if (emulator->V[x] != nn) {
                emulator->PC += 2;
            }
            break;
        case 0x5: // 0x5XY0: Skip if VX equals VY
            printf("0x5XY0 - Skipping if VX equals VY\n");
            if (emulator->V[x] == emulator->V[y]) {
                emulator->PC += 2;
            }
            break;
        case 0x6: // 0x6XNN: Set VX to NN
            printf("0x6XNN - Setting VX to NN\n");
            emulator->V[x] = nn;
            break;
        case 0x7: // 0x7XNN: Add NN to VX
            printf("0x7XNN - Adding NN to VX\n");
            emulator->V[x] += nn;
            break;
        case 0x8:
            switch (n) {
                case 0x0: // 8XY0: Set VX to VY
                    printf("8XY0: Setting VX to VY\n");
                    emulator->V[x] = emulator->V[y];
                    break;
                case 0x1:; // 8XY1: Binary OR
                    printf("8XY1: Binary OR of VX and VY\n");
                    emulator->V[x] |= emulator->V[y];
                    break;
                case 0x2: // 8XY2: Binary AND
                    printf("8XY2: Binary AND of VX and VY\n");
                    emulator->V[x] &= emulator->V[y];
                    break;
                case 0x3:; // 8XY3: Binary XOR
                    printf("8XY3: Binary XOR of VX and VY\n");
                    emulator->V[x] ^= emulator->V[y];
                    break;
                case 0x4: // 8XY4: Add
                    printf("8XY4: Adding VX and VY\n");
                    if ((emulator->V[x] + emulator->V[y]) > 0xFF) {
                        emulator->V[0xF] = 1;
                    } else {
                        emulator->V[0xF] = 0;
                    }
                    emulator->V[x] += emulator->V[y];
                    break;
                case 0x5:; // 8XY5: Subtract VY from VX
                    printf("8XY5: Subtracting VY from VX\n");
                    if (emulator->V[x] > emulator->V[y]) {
                        emulator->V[0xF] = 1;
                    } else {
                        emulator->V[0xF] = 0;
                    }
                    emulator->V[x] -= emulator->V[y];
                    break;
                case 0x6: // 8XY6: Shift right
                    printf("8XY6: Shifting right\n");
                    emulator->V[x] = emulator->V[y];
                    uint8_t shft_r = emulator->V[x] & 0x000F;
                    emulator->V[x] >>= 1;
                    if (shft_r == 1) {
                        emulator->V[0xF] = 1;
                    } else {
                        emulator->V[0xF] = 0;
                    }
                    break;
                case 0x7:; // 8XY7: Subtract VX from VY
                    printf("8XY7: Subtracting VX from VY\n");
                    if (emulator->V[y] > emulator->V[x]) {
                        emulator->V[0xF] = 1;
                    } else {
                        emulator->V[0xF] = 0;
                    }
                    emulator->V[x] = emulator->V[y] - emulator->V[x];
                    break;
                case 0xE:; // 8XYE: Shift left
                    printf("8XYE: Shifting left\n");
                    emulator->V[x] = emulator->V[y];
                    uint8_t shft_l = emulator->V[x] & 0x000F;
                    emulator->V[x] <<= 1;
                    if (shft_l == 1) {
                        emulator->V[0xF] = 1;
                    } else {
                        emulator->V[0xF] = 0;
                    }
                    break;
                default:
                    // This case doesn't exist!
                    printf("0x%04X - Unknown instruction\n", instruction);
                    return false;
            }
            break;
        case 0x9: // 9XY0: Skip if VX does not equal VY
            printf("0x9XY0 - Skipping if VX does not equal VY\n");
            if (emulator->V[x] != emulator->V[y]) {
                emulator->PC += 2;
            }
            break;
        case 0xA: // ANNN: Set index register
            printf("0xANNN - Setting index register to NNN\n");
            emulator->I = nnn;
            break;
        case 0xB: // BNNN: Jump with offset
            printf("0xBNNN - Jumping with offset\n");
            emulator->PC += nnn + emulator->V[0];
            break;
        case 0xC: // CXNN: Random
            printf("0xCXNN - Generating random number\n");
            uint8_t random = rand() % nn + 1; // Rand has limited randomness, but it's okay for this application
            emulator->V[x] = nn & random;
            break;
        case 0xD: // DXYN: Display
            printf("0xDXYN - Displaying sprite\n");
            // This can be done with modulo, but bitwise AND should be the same speed or better in most cases
            uint16_t xc = emulator->V[x] & 63;
            uint16_t yc = emulator->V[y] & 31;
            emulator->V[0xF] = 0;

            for (size_t row = 0; row < n; row++) {
                uint16_t pixel = emulator->memory[emulator->I + row];
                for (size_t bit = 0; bit < 8; bit++) {
                    if ((pixel & (0x80 >> bit)) != 0) {

                        if (emulator->display[xc + bit][yc + row] == true) {
                            emulator->V[0xF] = 1;
                        }

                        // set pixel value by using XOR
                        emulator->display[xc + bit][yc + row] ^= 1;
                    }
                }
            }
            break;
        case 0xE:
            switch (y) {
                case 0x9: // EX9E: Skip if key is pressed
                    printf("EX9E: Skipping if key is pressed\n");
                    if (emulator->keypad[emulator->V[x]] == true) {
                        emulator->PC += 2;
                    }
                    break;
                case 0xA:; // EXA1: Skip if key is not pressed
                    printf("EXA1: Skipping if key is not pressed\n");
                    if (emulator->keypad[emulator->V[x]] == false) {
                        emulator->PC += 2;
                    }
                    break;
                default:
                    // This case doesn't exist!
                    printf("0x%04X - Unknown instruction\n", instruction);
                    return false;
            }
            break;
        case 0xF:
            switch (nn) {
                case 0x07: // FX07: Set VX to the delay timer
                    printf("FX07: Setting VX to the delay timer\n");
                    emulator->V[x] = emulator->delay_timer;
                    break;
                case 0x0A:; // FX0A:
                    break;
                case 0x15:; // FX15: Set the delay timer to VX
                    printf("FX15: Setting the delay timer to VX\n");
                    emulator->delay_timer = emulator->V[x];
                    break;
                case 0x18:; // FX18: Set the sound timer to VX
                    printf("FX18: Setting the sound timer to VX\n");
                    emulator->sound_timer = emulator->V[x];
                    break;
                case 0x1E:; // FX1E: Add VX to I
                    if (emulator->I + emulator->V[x] > 0x1000) {
                        emulator->V[0xF] = 1;
                    }

                    emulator->I += emulator->V[x];
                    break;
                case 0x29:; // FX29:
                    break;
                case 0x33:; // FX33:
                    break;
                case 0x55:; // FX55:
                    break;
                case 0x65:; // FX65:
                    break;
                default:
                    // This case doesn't exist!
                    printf("0x%04X - Unknown instruction\n", instruction);
                    return false;
            }
            break;
        default:
            printf("0x%04X - Unknown instruction\n", instruction);
            return false;
    }

    printf("PC is currently at: 0x%04X\n", emulator->PC);

    return true;
}
