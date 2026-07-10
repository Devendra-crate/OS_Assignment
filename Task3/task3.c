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
void createFile();
void writeFile();
void readFile();
void deleteFile();
void setPermission();
void encryptFile();
void decryptFile();
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
// Create File
// Creates a new empty file specified by the user.
// If the file already exists, it will simply be
// opened and closed.
// --------------------------------------------------
void createFile()
{
    char filename[100];

    printf("\nEnter Filename to create file : ");
    scanf("%99s", filename);

    // Open file in write mode
    FILE *fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Unable to create file.\n");
        return;
    }

    fclose(fp);

    printf("File created successfully.\n");

    // Record this action
    logAction("File Created");
}

// --------------------------------------------------
// Write File
// Opens an existing file in append mode and allows
// the user to enter text. The entered text is stored
// at the end of the file.
// --------------------------------------------------
void writeFile()
{
    char filename[100];
    char text[500];

    printf("\nEnter Filename: ");
    scanf("%99s", filename);

    getchar();

    printf("Enter Text: ");
    fgets(text, sizeof(text), stdin);

    FILE *fp = fopen(filename, "a");

    if (fp == NULL)
    {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(fp, "%s", text);

    fclose(fp);

    printf("Data written successfully.\n");

    // Record the modification
    logAction("File Modified");
}


// --------------------------------------------------
// Read File
// Opens the selected file in read mode and displays
// its contents on the screen.
// --------------------------------------------------
void readFile()
{
    char filename[100];
    char ch;

    printf("\nEnter Filename: ");
    scanf("%99s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found.\n");
        return;
    }

    printf("\n========== File Content ==========\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }

    fclose(fp);

    printf("\n==================================\n");

    // Record file access
    logAction("File Read");
}

// --------------------------------------------------
// Delete File
// Removes the selected file from the system.
// If the file exists, it is permanently deleted.
// Otherwise an error message is displayed.
// --------------------------------------------------
void deleteFile()
{
    char filename[100];

    printf("\nEnter Filename: ");
    scanf("%99s", filename);

    // Attempt to delete the file
    if (remove(filename) == 0)
    {
        printf("File deleted successfully.\n");

        // Record this action
        logAction("File Deleted");
    }
    else
    {
        printf("Unable to delete file.\n");
    }
}


// --------------------------------------------------
// File Permission Management
// Changes the file permission to 755
// Owner  : Read, Write, Execute
// Group  : Read and Execute
// Others : Read and Execute
// --------------------------------------------------
void setPermission()
{
    char filename[100];

    printf("\nEnter Filename: ");
    scanf("%99s", filename);

    // Change permission to rwxr-xr-x
    if (chmod(filename, 0755) == 0)
    {
        printf("File permissions changed successfully.\n");
        printf("New Permission : 755 (rwxr-xr-x)\n");

        // Record permission change
        logAction("Permissions Changed");
    }
    else
    {
        printf("Unable to change permissions.\n");
    }
}


// --------------------------------------------------
// File Encryption
// Encrypts the contents of the selected file using
// a simple Caesar Cipher (+3).
// Each character is shifted three positions forward.
// --------------------------------------------------
void encryptFile()
{
    char filename[100];
    char ch;

    printf("\nEnter Filename: ");
    scanf("%99s", filename);

    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL)
    {
        printf("File not found.\n");

        if (temp != NULL)
            fclose(temp);

        return;
    }

    // Encrypt each character
    while ((ch = fgetc(fp)) != EOF)
    {
        fputc(ch + 3, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    printf("File encrypted successfully.\n");

    // Record encryption
    logAction("File decrypted successfully.\n");
}

// --------------------------------------------------
// File Decryption
// Restores the original file contents by shifting
// every encrypted character three positions back.
// ---------------------------------------- 

// --------------------------------------------------
// File Decryption
// Restores the original file contents by shifting
// every encrypted character three positions back.
// --------------------------------------------------
void decryptFile()
{
    char filename[100];
    char ch;

    printf("\nEnter Filename: ");
    scanf("%99s", filename);

    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL)
    {
        printf("File not found.\n");

        if (temp != NULL)
            fclose(temp);

        return;
    }

    // Decrypt each character
    while ((ch = fgetc(fp)) != EOF)
    {
        fputc(ch - 3, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(filename);
    rename("temp.txt", filename);

    printf("File decrypted successfully.\n");

    // Record decryption
    logAction("File Decrypted");
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

    createFile();

    writeFile();

    readFile();

    setPermission();

    encryptFile();

    decryptFile();

    deleteFile();

    return 0;
}
