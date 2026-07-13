#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define USERNAME "Devendra"
#define PASSWORD "password123"
#define MAX_CLIENTS 5

typedef struct
{
    char username[50];
    char password[50];
} Login;

int main()
{
    printf("=====================================\n");
    printf("      Server Application Started\n");
    printf("=====================================\n");

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress;
    socklen_t addressLength = sizeof(serverAddress);

    char buffer[BUFFER_SIZE];
    Login login;
    int bytesReceived;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSocket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    printf("Server socket created successfully.\n");

    // Configure server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind
    if (bind(serverSocket,
             (struct sockaddr *)&serverAddress,
             sizeof(serverAddress)) < 0)
    {
        printf("Binding failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("Server bound to Port %d successfully.\n", PORT);

    // Listen
    if (listen(serverSocket, MAX_CLIENTS) < 0)
    {
        printf("Listening failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("Server is listening for client connections...\n");

    // Accept
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

    // Receive Login
    bytesReceived = recv(clientSocket, &login, sizeof(login), 0);

    if (bytesReceived <= 0)
    {
        printf("Failed to receive login.\n");
        close(clientSocket);
        close(serverSocket);
        return 1;
    }

    printf("\nClient Authentication Request\n");
    printf("Username : %s\n", login.username);
    printf("Password : %s\n", login.password);

    // Authenticate
    if (strcmp(login.username, USERNAME) == 0 &&
        strcmp(login.password, PASSWORD) == 0)
    {
        printf("\nAuthentication Successful!\n");

        bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0';

            printf("\nMessage received from client:\n");
            printf("%s\n", buffer);
        }
    }
    else
    {
        printf("\nAuthentication Failed!\n");
    }

    close(clientSocket);
    close(serverSocket);

    return 0;
}
