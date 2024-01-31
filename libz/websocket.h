#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <curl/curl.h>
#ifndef WEBSOCKET_H
#define WEBSOCKET_H

size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    char *ptr = (char *)contents;

    // Assuming you want to print the response data to the console
    printf("%.*s", (int)realsize, ptr);

    // You might also want to handle the data in some other way (e.g., store it in a buffer)

    return realsize;
}


// Function to check if a host is up using a HEAD request with libcurl
int static inline check_host(const char* url){
    volatile status_code;
    CURL *curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, url);
        // Set the HTTP method to HEAD
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);

        // Set a callback function to handle the response data (optional)
        // (Note: The write_callback function should be defined somewhere in your code)
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the HTTP request
        CURLcode res = curl_easy_perform(curl);

        // Check the result of the request
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Host is up!\n");
            return 0;
        }
    } else {
        fprintf(stderr, "Could not initialize curl.\n");
        return -1;
    }
    return 0;
}

// Function to send an HTTP GET request to a server using sockets
void send_socket(const char* hostname, const char* port) {
    const char *request = "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n";

    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Resolve hostname to IP address using getaddrinfo
    struct addrinfo hints, *result, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;     // Use either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // Use TCP

    // Resolve hostname to IP address using getaddrinfo
    int status = getaddrinfo(hostname, port, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Iterate through the result list and connect to the first available address
    for (p = result; p != NULL; p = p->ai_next) {
        clientSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (clientSocket == -1) {
            perror("Error creating socket");
            continue;
        }

        if (connect(clientSocket, p->ai_addr, p->ai_addrlen) == -1) {
            close(clientSocket);
            perror("Error connecting to server");
            continue;
        }

        break; // Successfully connected
    }

    // Free the addrinfo structure
    freeaddrinfo(result);

    if (clientSocket == -1) {
        fprintf(stderr, "Failed to connect to the server\n");
        exit(EXIT_FAILURE);
    }

    // Send the HTTP GET request
    char fullRequest[4096];
    snprintf(fullRequest, sizeof(fullRequest), request, hostname);
    if (send(clientSocket, fullRequest, strlen(fullRequest), 0) == -1) {
        perror("Error sending request");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    // Receive and print the response
    char buffer[4096];
    ssize_t bytesRead;
    while ((bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesRead] = '\0';
        printf("%s", buffer);
    }

    // Close the socket
    close(clientSocket);
}

#endif
