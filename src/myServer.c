#include "headerFiles.h"
#define SERVER_PORT 8000

int main()
{
    // declare and define the essential variables
    int socketDescriptor;          // socket descriptor (reference)
    int len;                       // length of string to be echoed
    char buffer[256];              // data buffer
    struct sockaddr_in serverAddr; // server (local) socket address
    struct sockaddr_in clientAddr; // client (remote) socket address
    socklen_t clientAddressLen;    // length of client socket address

    // build the local server socket address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;                // family field
    serverAddr.sin_port = htons(SERVER_PORT);       // default port number (8000)
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // default IP address

    // create the socket
    if ((socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error: Socket creation failed!");
        exit(1);
    }

    // bind socket to local address and port
    if (bind(socketDescriptor, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Error: Bind failed!");
        close(socketDescriptor);
        exit(1);
    }

    printf("Server is running on port %d...\n", SERVER_PORT);

    for (;;)
    {                                          // Run forever
        clientAddressLen = sizeof(clientAddr); // Initialize clientAddressLen
        // Receive string
        len = recvfrom(socketDescriptor, buffer, sizeof(buffer) - 1, 0,
                       (struct sockaddr *)&clientAddr, &clientAddressLen);

        if (len < 0)
        {
            perror("Error: Receiving message failed!");
            continue; // Skip to the next iteration
        }

        buffer[len] = '\0'; // Null-terminate the received data
        printf("Received: %s\n", buffer);

        // Send string back to client
        if (sendto(socketDescriptor, buffer, len, 0,
                   (struct sockaddr *)&clientAddr, clientAddressLen) < 0)
        {
            perror("Error: Sending message failed!");
        }
    }

    // Close the socket (never reached due to infinite loop)
    close(socketDescriptor);

    return 0;
}
