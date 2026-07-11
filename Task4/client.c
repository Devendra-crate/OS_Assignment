/*
=========================================================
Task 4 : Network Programming and IPC
Client Program

Features to be implemented:
1. Connect to Server
2. Authentication
3. Send Messages
4. Receive Messages
5. Graceful Exit

Author : Devendra Chhetri
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

// Function Prototypes
int main();

int main()
{
    printf("=====================================\n");
    printf("      Client Application Started\n");
    printf("=====================================\n");

    int clientSocket;

    struct sockaddr_in serverAddress;
    char buffer[BUFFER_SIZE];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    printf("Client socket created successfully.\n");

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(clientSocket,
                (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0)
    {
        printf("Connection failed.\n");

        close(clientSocket);

        return 1;
    }

    printf("Connected to server successfully!\n");

     
     // Enter a Message
     
    printf("Enter message: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    
    // Send Message to Server
    send(clientSocket, buffer, strlen(buffer), 0);

    printf("Message sent successfully.\n");
    close(clientSocket);

    return 0;
}
