#include "../include/main.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>", argv[0]);
        return EXIT_FAILURE;
    }

    initialize_graphics();
    chip8_run(argv[1]);

    return EXIT_SUCCESS;
}

