#include "headerFiles.h"
#define SERVER_PORT 8000

int main()
{
    // declare and define the essential variable
    int socketDescriptor;          // socker descriptor ( reference )
    int len;                       // length of string to be echoed
    char buffer[256];              // data buffer
    struct sockaddr_in serverAddr; // server ( local ) socket address
    struct sockaddr_in clientAddr; // client ( remote ) socket address
    socklen_t clientAddressLen;    // length of client socket address

    // build the local server socket address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;                // family field
    serverAddr.sin_port = htons(SERVER_PORT);       // default port number ( 8000 )
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY); // default IP Address

    // create the socket
    if ((socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error : Socker Failed ! ");
        exit(1);
    }

    // bind socket to local address and port
    if (bind(socketDescriptor, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("Error : Bind Failed !");
        close(socketDescriptor);
        exit(1);
    }

    for (;;)
    {
        clientAddressLen = sizeof(clientAddr);

        len = recvfrom(socketDescriptor, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&clientAddr, &clientAddressLen);

        printf("Received: %s\n", buffer);

        sendto(socketDescriptor, buffer, len, 0, (struct sockaddr *)&clientAddr, clientAddressLen);
    }

    close(socketDescriptor);

    return 0;
}