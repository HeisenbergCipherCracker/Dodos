#include <stdio.h>
#include <string.h>
#include "types.h"

char* host = NULL;
char* port = NULL;
char* path = NULL;
char* method = NULL;
char* body = NULL;
char* header = NULL;
char* timeout = NULL;
char* user = NULL;
char* password = NULL;
char* cert = NULL;
char* key = NULL;
char* ca = NULL;
char* insecure = NULL;
char* debug = NULL;
char* verbose = NULL;
char* help = NULL;


int cmdline(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) { // Start from index 1 to skip the program name (argv[0])
        if (strcmp(argv[i], "--host") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                host = argv[i + 1];
                i++; // Skip the next argument (value)
            }
        } else if (strcmp(argv[i], "--port") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                port = argv[i + 1];
                i++; // Skip the next argument (value)
            }
        }
        else if (strcmp(argv[i],"--timeout") == 0){
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                timeout = argv[i + 1];
                i++; // Skip the next argument (value)
            }
        }
    }

    // Now you can use host and port globally in your program
    if (host != NULL) {
        printf("Host: %s\n", host);
    }
    if (port != NULL) {
        printf("Port: %s\n", port);
    }

    return 0;
}