#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "settings.h"
#include <arpa/inet.h>
#include "settings.h"
#include <unistd.h> 

void request(const char*host,int port) {
    int sockfd;
    struct sockaddr_in serverAddr;

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(EXIT_FAILURE);
    }

    // Set up the server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(host); // Google's IP address

    // Connect to the server
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        print_error_msg("Error in connect");
        exit(EXIT_FAILURE);
    }

    // Data to send
    char data[100];
    int dataLen = strlen(data);
    snprintf(data, sizeof(data), "GET / HTTP/1.1\r\nHost: %s\r\n\r\n", host);


    // Print the request
    printf("Request: %s\n", data);

    // Send the data
    if (send(sockfd, data, dataLen, 0) != dataLen) {
        perror("Error in send");
        exit(EXIT_FAILURE);
    }

    // Close the socket
    close(sockfd);

}
