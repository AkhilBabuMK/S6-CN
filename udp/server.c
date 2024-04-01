#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
    char buffer[1024] = { 0 };
    int serverSocket, addrlen, bytesReceived;
    struct sockaddr_in serverAddr, clientAddr;

    // Create UDP socket
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Set server address and port
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(serverSocket, (const struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is running and listening on port %d\n", PORT);

    while (1) {
        char hello[100] = { 0 };
        addrlen = sizeof(clientAddr);

        // Receive data from client
        bytesReceived = recvfrom(serverSocket, buffer, 1024, 0, (struct sockaddr*)&clientAddr, (socklen_t*)&addrlen);
        if (bytesReceived < 0) {
            perror("recvfrom failed");
            exit(EXIT_FAILURE);
        }

        printf("%s received from client\n\n", buffer);

        printf("Enter message from server: ");
        fgets(hello, sizeof(hello), stdin);
        hello[strcspn(hello, "\n")] = '\0'; // Remove newline character

        // Send data to client
        if (sendto(serverSocket, hello, strlen(hello), 0, (const struct sockaddr*)&clientAddr, addrlen) < 0) {
            perror("sendto failed");
            exit(EXIT_FAILURE);
        }

        printf("%s message sent to client\n\n", hello);

        if (strcmp(hello, "exit") == 0) {
            printf("Server closed\n");
            break;
        }
    }

    close(serverSocket);
    return 0;
}
