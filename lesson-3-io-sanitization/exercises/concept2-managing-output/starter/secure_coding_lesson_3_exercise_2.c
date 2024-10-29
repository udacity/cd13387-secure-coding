#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Hardcoded password
#define PASSWORD "s3CretP4ssword"

// Function prototypes
void check_password();
void diagnostics_output(const char *input, const char *password, void *crash_addr);

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

    // Comparison (not actually secure due to potential overflow)
    if (strcmp(buffer, PASSWORD) == 0) {
        printf("Access granted.\n");
    } else {
        printf("Access denied.\n");
    }

    // Simulate a crash by detecting an overflow
    if (strlen(buffer) > sizeof(buffer)) {
        diagnostics_output(input, PASSWORD, __builtin_return_address(0));
    }
}

// Diagnostic output on buffer overflow
void diagnostics_output(const char *input, const char *password, void *crash_addr) {
    printf("\n*** Diagnostics Output ***\n");
    printf("Crash occurred at address: %p\n", crash_addr);
    printf("Input password: %s\n", input);
    printf("Memory dump:\n");

    for (int i = 0; i < strlen(PASSWORD); i++) {
        printf("0x%02X: %02X vs %02X\n", i, (unsigned char)input[i], (unsigned char)password[i]);
    }

    exit(1);
}