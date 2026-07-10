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

// Function Prototypes
void logAction(char action[]);
int login();
int main();

// --------------------------------------------------
// Audit Logging
// Records important system events such as successful
// login, file creation, deletion and modifications.
// Every action is stored in "audit.log" with the
// current date and time.
// --------------------------------------------------
void logAction(char action[])
{
    FILE *log = fopen("audit.log", "a");

    if (log == NULL)
    {
        printf("Unable to open audit log.\n");
        return;
    }

    time_t t;
    time(&t);

    fprintf(log, "%s : %s", action, ctime(&t));

    fclose(log);
}


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

// Record the successful login
    logAction("User logged in");

    return 1;
    }

    printf("\nInvalid Username or Password!\n");

   // Record failed login attempt
    logAction("Failed login attempt");

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
