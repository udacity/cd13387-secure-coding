#include <stdio.h>
#include <string.h>


void buffer_overflow_function(const char *input) {
    char deviceName[10];  // Buffer with a size of 10 bytes

    // Safe copy using strncpy with ensuring null termination
    strncpy(deviceName, input, sizeof(deviceName) - 1);

    // Ensure null termination
    deviceName[sizeof(deviceName) - 1] = '\0';


    printf("Device name is: %s\n", deviceName);
}


int main() {
    char userInput[100];  // Temporary storage for user input

    printf("Enter device name: ");
    fgets(userInput, sizeof(userInput), stdin);  // Read user input


    // Remove newline character if present
    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';
    }

    buffer_overflow_function(userInput);

    return 0;
}