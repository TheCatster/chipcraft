#include "main.h"

int main(int argc, char *argv[]) {
    initialize_graphics();
    chip8_run();

    return EXIT_SUCCESS;
}

