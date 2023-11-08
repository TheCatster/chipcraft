#include "../include/main.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen("chipcraft.log", "w+");
    if (!fp) {
        perror("File opening failed");
        return EXIT_FAILURE;
    }

    log_add_fp(fp, 0);
    log_set_quiet(true);

    initialize_graphics();
    chip8_run(argv[1]);

    return EXIT_SUCCESS;
}

