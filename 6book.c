#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define BLOCKS 100
#define BLOCK_SIZE 1024

void sigint_handler(int signum) {
    void *blocks[BLOCKS];
    for (int i = 0; i < BLOCKS; i++) {
        blocks[i] = malloc(BLOCK_SIZE);
        if (blocks[i] == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < BLOCKS; i++) {
        free(blocks[i]);
    }
}

int main() {
    signal(SIGINT, sigint_handler);

    while (1) {
        void *blocks[BLOCKS];
        for (int i = 0; i < BLOCKS; i++) {
            blocks[i] = malloc(BLOCK_SIZE);
            if (blocks[i] == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
        }
        for (int i = 0; i < BLOCKS; i++) {
            free(blocks[i]);
        }
    }

    return 0;
}
