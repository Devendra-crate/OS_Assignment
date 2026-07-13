#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

typedef struct
{
    char username[50];
    char password[50];
} Login;

int main()
{
    printf("=====================================\n");
    printf("      Client Application Started\n");
    printf("=====================================\n");

    int clientSocket;

    struct sockaddr_in serverAddress;

    char buffer[BUFFER_SIZE];
    Login login;

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    {
        perror("Socket creation failed.\n");
        return 1;
    }

    printf("Client socket created successfully.\n");

    // Configure server
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect
    if (connect(clientSocket,
                (struct sockaddr *)&serverAddress,
                sizeof(serverAddress)) < 0)
    {
        perror("Connection failed.\n");
        close(clientSocket);
        return 1;
    }

    printf("Connected to server successfully!\n");

    // Login
    printf("Username: ");
    scanf("%49s", login.username);

    printf("Password: ");
    scanf("%49s", login.password);

    getchar();

    // Send Login
    if(send(clientSocket, &login, sizeof(login), 0) < 0)
    {
       perror("Login send failed");
       close(clientSocket);
       return 1;
    }

    // Send Message
    printf("Enter message: ");
    fgets(buffer, BUFFER_SIZE, stdin);

    if(send(clientSocket, buffer, strlen(buffer)+1, 0) < 0)
    {
       perror("Message send failed");
       close(clientSocket);
       return 1;
   }

    printf("Message sent successfully.\n");

    close(clientSocket);

    return 0;
}
