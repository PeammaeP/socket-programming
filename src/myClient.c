#include "headerFiles.h"

int main(int argc, char *argv[])
{
    // define & declare the essential variables
    int socketDescriptor; // socket descriptor
    socklen_t len;        // length of string to be echoed
    char *serverName;     // server name
    int serverPort;       // server port
    char *string;         // string to be echoed
    char buffer[256 + 1]; // data buffer
    struct sockaddr_in serverAddress;

    // check and set program arguments
    if (argc != 4)
    {
        printf("Error: Three arguments are needed!\n");
        exit(1);
    }

    // read and set program arguments
    serverName = argv[1];
    serverPort = atoi(argv[2]);
    string = argv[3];

    // build the server socket address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;

    if (inet_pton(AF_INET, serverName, &serverAddress.sin_addr) <= 0)
    {
        perror("Error: Invalid server address!");
        exit(1);
    }
    serverAddress.sin_port = htons(serverPort);

    // create the socket
    if ((socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error: Socket creation failed!");
        exit(1);
    }

    // send echo string
    len = strlen(string);
    if (sendto(socketDescriptor, string, len, 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Error: Sending message failed!");
        close(socketDescriptor);
        exit(1);
    }

    // receive the echo string
    if (recvfrom(socketDescriptor, buffer, sizeof(buffer) - 1, 0, NULL, NULL) < 0)
    {
        perror("Error: Receiving message failed!");
        close(socketDescriptor);
        exit(1);
    }

    // null-terminate the buffer
    buffer[len] = '\0';

    // print and verify echoed string
    printf("Echo String Received: %s", buffer);

    // close the socket
    close(socketDescriptor);

    // stop the program
    exit(0);

    return 0;
}
