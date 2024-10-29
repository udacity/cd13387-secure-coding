#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Hardcoded password
#define PASSWORD "s3CretP4ssword"

// Function prototypes
void check_password();
void diagnostics_output(const char *input, size_t buffersize);

int main() {
    check_password();
    return 0;
}

void check_password() {
    char buffer[20]; // Small buffer vulnerable to overflow
    char input[100]; // Large buffer to read input from stdin

    // Prompt user for password
    printf("Enter password: ");
    fgets(input, sizeof(input), stdin);

    // Remove trailing newline if it exists
    input[strcspn(input, "\n")] = 0;

    // Vulnerable strcpy - no bounds checking
    strcpy(buffer, input);

    // Comparison
    if (strcmp(buffer, PASSWORD) == 0) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    // Simulate a crash by detecting an overflow
    if (strlen(buffer) > sizeof(buffer)) {
        diagnostics_output(input, sizeof(buffer));
    }
}

// Diagnostic output on buffer overflow
void diagnostics_output(const char *input, size_t buffersize) {
    printf("\n*** Diagnostics Output ***\n");
    printf("Crash occurred.\n");
    printf("Input password: %s\n", input);
    printf("Size of input: %ld\n", strlen(input));
    printf("Size of buffer: %ld\n", buffersize);

    exit(1);

}