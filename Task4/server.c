/*
=========================================================
Task 4 : Network Programming and IPC
Server Program

Features to be implemented:
1. Socket Creation
2. Client Authentication
3. Data Exchange
4. Multiple Client Handling
5. Error Handling

Author : Devendra Chhetri
=========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>


#define PORT 8080
#define BUFFER_SIZE 1024
#define USERNAME "Devendra"
#define PASSWORD "password123"
#define MAX_CLIENTS 5

// Function Prototypes
int main();

int main()
{
    printf("=====================================\n");
    printf("      Server Application Started\n");
    printf("=====================================\n");

    int serverSocket;
    struct sockaddr_in serverAddress;
    int clientSocket;
    int bytesReceived;
    socklen_t addressLength = sizeof(serverAddress);
    char buffer[BUFFER_SIZE];
    char username[50];
    char password[50];
    // --------------------------------------------------
    // Create Server Socket
    // AF_INET  : IPv4
    // SOCK_STREAM : TCP Protocol
   // --------------------------------------------------
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
      printf("Socket creation failed.\n");
      return 1;
    }

    printf("Server socket created successfully.\n");


    // --------------------------------------------------
   // Configure Server Address
   // --------------------------------------------------
   serverAddress.sin_family = AF_INET;
   serverAddress.sin_addr.s_addr = INADDR_ANY;
   serverAddress.sin_port = htons(PORT);


   // --------------------------------------------------
   // Bind Socket
   // Associates the socket with Port 8080.
   // --------------------------------------------------
   if (bind(serverSocket,
         (struct sockaddr *)&serverAddress,
          sizeof(serverAddress)) < 0)
    {
      printf("Binding failed.\n");

      close(serverSocket);

      return 1;
    }

    printf("Server bound to Port %d successfully.\n", PORT);


    // --------------------------------------------------
    // Listen for Client Connections
    // --------------------------------------------------
    if (listen(serverSocket, MAX_CLIENTS) < 0)
    {
       printf("Listening failed.\n");

       close(serverSocket);

       return 1;
    }

    printf("Server is listening for client connections...\n");

    // --------------------------------------------------
    // Wait for a Client Connection
    // --------------------------------------------------
    clientSocket = accept(serverSocket,
                      (struct sockaddr *)&serverAddress,
                      &addressLength);

    if (clientSocket < 0)
    {
       printf("Client connection failed.\n");

       close(serverSocket);

       return 1;
    }

    printf("Client connected successfully!\n");

   
   // Receive Username
   recv(clientSocket, username, sizeof(username), 0);


   // Receive Password

   recv(clientSocket, password, sizeof(password), 0);

   printf("\nClient Authentication Request\n");
   printf("Username : %s\n", username);
   printf("Password : %s\n", password);

   // Validate Credentials

   if (strcmp(username, USERNAME) == 0 &&
       strcmp(password, PASSWORD) == 0)
   {
        printf("\nAuthentication Successful!\n");
   
       // Receive Client Message

       bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

       if (bytesReceived > 0)
       {
           buffer[bytesReceived] = '\0';

           printf("\nMessage received from client:\n");
           printf("%s", buffer);
       }

   }
   else
   {
      printf("\nAuthentication Failed!\n");

      close(clientSocket);
      close(serverSocket);

      return 0;
   }

   // --------------------------------------------------
   // Close Sockets
   // --------------------------------------------------
   close(clientSocket);
   close(serverSocket);

   return 0;
}
