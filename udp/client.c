#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h> // Include the standard library header for EXIT_FAILURE

#define PORT 8080
#define SERVER_IP "127.0.0.1"

int main(int argc, char const* argv[])
{
    int clientSocket, bytesReceived;
    char hello[100];
    struct sockaddr_in serverAddr;

    // Create UDP socket
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address and port
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
        perror("invalid address");
        exit(EXIT_FAILURE);
    }

    while (1) {
        char buffer[1024] = { 0 };

        printf("Enter message from client: ");
        fgets(hello, sizeof(hello), stdin);
        hello[strcspn(hello, "\n")] = '\0'; // Remove newline character

        if (strcmp(hello, "exit") == 0) {
            printf("Client terminated\n");
            break;
        }

        // Send data to server
        if (sendto(clientSocket, hello, strlen(hello), 0, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        printf("%s message sent to server\n\n", hello);

        // Receive data from server
        bytesReceived = recvfrom(clientSocket, buffer, 1024, 0, NULL, NULL);
        if (bytesReceived < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        printf("%s received from server\n\n", buffer);
    }

    close(clientSocket);
    return 0;
}
