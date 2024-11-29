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
        printf("Error : Three Arguments are needed!");
        exit(1);
    }

    // read and set program arguments
    serverName = argv[1];
    serverPort = atoi(argv[2]);
    string = argv[3];

    // build the server socket address
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    inet_pton(AF_INET, serverName, &serverAddress.sin_addr);
    serverAddress.sin_port = htons(serverPort);

    // create the socket
    if ((socketDescriptor = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("Error : Socket Failed !");
        exit(1);
    }

    // send echo string
    len = sendto(socketDescriptor, string, strlen(string), 0, (struct sockaddr *)&serverAddress, sizeof(serverAddress));

    recvfrom(socketDescriptor, buffer, sizeof(buffer) - 1, 0, NULL, NULL);

    buffer[len] = '\0';
    printf("Echo String Received .. %s\n ", buffer);

    // close the socket
    close(socketDescriptor);

    // stop the program
    exit(0);

    return 0;
}