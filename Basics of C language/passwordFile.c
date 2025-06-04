#include <stdio.h>
#include <string.h>

int main() {
    char fileUserName[100], filePassword[100];
    char enteredUserName[100], enteredPassword[100];
    FILE *fp;

    // Open file
    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read stored credentials from file
    fscanf(fp, " %[^\n;] ; %[^\n]", fileUserName, filePassword);
    fclose(fp);

    // Ask user for input
    printf("Enter full username: ");
   // getchar(); // consume newline left by previous input
    fgets(enteredUserName, sizeof(enteredUserName), stdin);
    enteredUserName[strcspn(enteredUserName, "\n")] = '\0'; // remove newline

    printf("Enter password: ");
    fgets(enteredPassword, sizeof(enteredPassword), stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0'; // remove newline

    // Debug print (optional)
    printf("\nEntered: %s ; %s\n", enteredUserName, enteredPassword);
    printf("From file: %s ; %s\n", fileUserName, filePassword);

    // Compare
    if (strcmp(fileUserName, enteredUserName) == 0 &&
        strcmp(filePassword, enteredPassword) == 0) {
        printf("You are logged in successfully\n");
    } else {
        printf("Invalid Username or Password\n");
    }

    return 0;
}

