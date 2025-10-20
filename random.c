#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RANGE_MIN 1
#define RANGE_MAX 100
#define BUF_SIZE 100

static int random_in_range(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

int main(void) {
    char buf[BUF_SIZE];
    int target, guess, attempts;
    char *endptr;

    /* Seed RNG with time and address entropy for better variation across runs */
    srand((unsigned)(time(NULL) ^ (uintptr_t)(void *)&main));

    printf("Guess the number between %d and %d.\n", RANGE_MIN, RANGE_MAX);
    printf("Type 'q' or 'quit' to exit.\n\n");

    target = random_in_range(RANGE_MIN, RANGE_MAX);
    attempts = 0;

    while (1) {
        printf("Enter your guess: ");
        if (!fgets(buf, sizeof buf, stdin)) {
            puts("\nInput error. Exiting.");
            return 1;
        }

        /* strip newline */
        buf[strcspn(buf, "\r\n")] = '\0';

        if (strcmp(buf, "q") == 0 || strcmp(buf, "quit") == 0) {
            printf("Quit. The number was %d.\n", target);
            return 0;
        }

        /* parse integer safely */
        guess = (int)strtol(buf, &endptr, 10);
        if (endptr == buf || *endptr != '\0') {
            puts("Invalid input. Enter an integer, or 'q' to quit.");
            continue;
        }

        if (guess < RANGE_MIN || guess > RANGE_MAX) {
            printf("Please guess a number between %d and %d.\n", RANGE_MIN, RANGE_MAX);
            continue;
        }

        attempts++;

        if (guess < target) {
            puts("Too low.");
        } else if (guess > target) {
            puts("Too high.");
        } else {
            printf("Correct! You guessed %d in %d attempt%s.\n", target, attempts, attempts == 1 ? "" : "s");
            /* prompt for replay */
            printf("Play again? (y/n): ");
            if (!fgets(buf, sizeof buf, stdin)) return 0;
            if (buf[0] == 'y' || buf[0] == 'Y') {
                target = random_in_range(RANGE_MIN, RANGE_MAX);
                attempts = 0;
                printf("\nNew game! Guess the number between %d and %d.\n", RANGE_MIN, RANGE_MAX);
                continue;
            } else {
                puts("Goodbye.");
                break;
            }
        }
    }

    return 0;
}