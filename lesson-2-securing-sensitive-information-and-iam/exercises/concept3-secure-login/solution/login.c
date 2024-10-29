#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <ctype.h>

#define DEFAULT_USERNAME "admin"
#define DEFAULT_PASSWORD "admin"
#define STATUS_FILE "status.bin"
#define SALT "RANDOM" // Use a 6-character salt
#define MAX_FAILED_ATTEMPTS 3

typedef struct {
    char username[50];
    char hashed_password[65];
    int failed_attempts;
    int user_blocked;
} UserStatus;

void hash_password(const char *password, char *hashed_password) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_MD_CTX *mdctx;

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(mdctx, password, strlen(password));
    EVP_DigestUpdate(mdctx, SALT, strlen(SALT));
    EVP_DigestFinal_ex(mdctx, hash, &hash_len);
    EVP_MD_CTX_free(mdctx);

    for (unsigned int i = 0; i < hash_len; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }
    hashed_password[hash_len * 2] = 0;
}

int verify_password(const char *input_password, const char *stored_hash) {
    char hashed_input[65];
    hash_password(input_password, hashed_input);
    return strcmp(hashed_input, stored_hash) == 0;
}

int is_password_strong(const char *password) {
    if (strlen(password) < 12) return 0;

    int has_upper = 0, has_lower = 0, has_digit = 0, has_special = 0;
    for (int i = 0; password[i]; i++) {
        if (isupper(password[i])) has_upper = 1;
        else if (islower(password[i])) has_lower = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else if (ispunct(password[i])) has_special = 1;
    }

    return has_upper && has_lower && has_digit && has_special;
}

void set_password(UserStatus *status) {
    char new_password[100], hashed_password[65];
    printf("Enter new password: ");
    scanf("%s", new_password);

    if (!is_password_strong(new_password)) {
        printf("Password must be at least 12 characters long and include at least one lowercase letter, one uppercase letter, one digit, and one special character.\n");
        return;
    }

    hash_password(new_password, hashed_password);
    strcpy(status->hashed_password, hashed_password);

    FILE *file = fopen(STATUS_FILE, "w");
    if (file == NULL) {
        perror("Failed to open status file");
        exit(EXIT_FAILURE);
    }
    fwrite(status, sizeof(UserStatus), 1, file);
    fclose(file);

    printf("Password updated successfully.\n");
}

void initialize_status_file() {
    FILE *file = fopen(STATUS_FILE, "r");
    if (file == NULL) {
        UserStatus status = {0};
        strcpy(status.username, DEFAULT_USERNAME);
        hash_password(DEFAULT_PASSWORD, status.hashed_password);
        status.failed_attempts = 0;
        status.user_blocked = 0;

        file = fopen(STATUS_FILE, "w");
        if (file == NULL) {
            perror("Failed to open status file");
            exit(EXIT_FAILURE);
        }
        fwrite(&status, sizeof(UserStatus), 1, file);
        fclose(file);
    } else {
        fclose(file);
    }
}

void read_status(UserStatus *status) {
    FILE *file = fopen(STATUS_FILE, "r");
    if (file != NULL) {
        fread(status, sizeof(UserStatus), 1, file);
        fclose(file);
    } else {
        perror("Failed to open status file");
        exit(EXIT_FAILURE);
    }
}

void write_status(const UserStatus *status) {
    FILE *file = fopen(STATUS_FILE, "w");
    if (file != NULL) {
        fwrite(status, sizeof(UserStatus), 1, file);
        fclose(file);
    } else {
        perror("Failed to open status file");
        exit(EXIT_FAILURE);
    }
}

int main() {
    char command[50], username[50], password[50];
    UserStatus status;

    initialize_status_file();
    read_status(&status);

    printf("Enter username: ");
    scanf("%s", username);

    if (strcmp(username, status.username) != 0) {
        printf("Invalid username.\n");
        exit(EXIT_FAILURE);
    }

    if (status.user_blocked) {
        printf("User is blocked due to too many failed login attempts.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter password: ");
    scanf("%s", password);

    if (verify_password(password, status.hashed_password)) {
        printf("Login successful.\n");
        status.failed_attempts = 0;
        write_status(&status);
    } else {
        printf("Invalid password.\n");
        status.failed_attempts++;
        if (status.failed_attempts >= MAX_FAILED_ATTEMPTS) {
            status.user_blocked = 1;
            printf("User is blocked due to too many failed login attempts.\n");
        }
        write_status(&status);
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("> ");
        scanf("%s", command);

        if (strcmp(command, "setpassword") == 0) {
            set_password(&status);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command.\nAllowed commands are setpassword and exit.\n");
        }
    }

    return 0;
}    