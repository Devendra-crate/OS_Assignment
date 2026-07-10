/*
----------------------------------------------------------
Task 3 : Secure File Management System
Course : Operating Systems

This program demonstrates:
1. User Authentication
2. File Operations
3. File Permissions
4. Encryption and Decryption
5. Audit Logging

Author : Devendra Chhetri
----------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

// -------------------------------
// Default Login Credentials
// -------------------------------
#define USERNAME "Devendra"
#define PASSWORD "password123"

// Function Prototypes
// --------------------------------------------------
// User Authentication
// Checks whether the entered username and password
// match the predefined administrator credentials.
// --------------------------------------------------
int login()
{
    char username[50];
    char password[50];

    printf("Username: ");
    scanf("%49s", username);

    printf("Password: ");
    scanf("%49s", password);

    if (strcmp(username, USERNAME) == 0 &&
        strcmp(password, PASSWORD) == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }

    printf("\nInvalid Username or Password!\n");
    return 0;
}


// --------------------------------------------------
// Main Function
// Starts the Secure File Management System.
// --------------------------------------------------
int main()
{
    printf("========================================\n");
    printf(" Secure File Management System\n");
    printf("========================================\n\n");

    if (!login())
        return 0;

    printf("\nAuthentication Completed Successfully.\n");

    return 0;
}
