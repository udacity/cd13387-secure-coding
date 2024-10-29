#include <stdio.h>
#include <string.h>


void buffer_overflow_function(const char *input) {
    char deviceName[10];  // Buffer with a size of 10 bytes

    strcpy(deviceName, input);

    printf("Device name is: %s\n", deviceName);
}


int main() {
    char userInput[100];  // Temporary storage for user input

    printf("Enter device name: ");
    fgets(userInput, sizeof(userInput), stdin);  // Read user input

    buffer_overflow_function(userInput);

    return 0;
}