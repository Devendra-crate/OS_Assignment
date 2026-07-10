/*
==========================================================
Task 3 : Secure File Management System

Features Implemented:
- User Authentication
- Audit Logging
- File Creation
- File Reading
- File Writing
- File Deletion
- File Permission Management
- File Encryption
- File Decryption

Author : Devendra Chhetri
==========================================================
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


// --------------------------------------------------
// User Authentication
// Allows only authorized users
// to access the file system.
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
// Creates a new empty file using the filename
// entered by the authenticated user.
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
// Opens a file in append mode and stores
// user input without deleting previous data.
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
// Displays the complete contents of
// the selected file.
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
// Permanently removes the selected file
// from the system.
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
// Encrypts every character using
// Caesar Cipher (+3).
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
// Restores the original file by
// reversing the Caesar Cipher (-3).
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
// Displays a menu and allows the user to perform
// different file operations until Exit is selected.
// --------------------------------------------------
int main()
{
    int choice;

    // User authentication
    if (!login())
        return 0;

    do
    {
        printf("\n");
        printf("=========================================\n");
        printf("   Secure File Management System\n");
        printf("=========================================\n");

        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Delete File\n");
        printf("5. Set Permissions\n");
        printf("6. Encrypt File\n");
        printf("7. Decrypt File\n");
        printf("8. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                createFile();
                break;

            case 2:
                writeFile();
                break;

            case 3:
                readFile();
                break;

            case 4:
                deleteFile();
                break;

            case 5:
                setPermission();
                break;

            case 6:
                encryptFile();
                break;

            case 7:
                decryptFile();
                break;

            case 8:
            printf("\nThank you for using the Secure File Management System.\n");
            printf("Program terminated successfully.\n");
            break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while (choice != 8);

    return 0;
}
