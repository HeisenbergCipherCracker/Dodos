#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef SHELL_H
#define SHELL_H
#include "common.h"
#include "host.h"
#include "settings.h"
#include "websocket.h"
#include "typedefs.h"


void shell(){
    printf(">>> ");
    char command[256];
    scanf("%s", command);
    if (strcmp(command, "exit") == 0) {
        exit(0);
    }
    if (strcmp(command, "help") == 0) {
        printf("exit\n");
    }
    if (strcmp(command,"run") == 0){
        char input[256] = "\nenter the url of the host:";
        printf(input);
        scanf("%s",input);
        gethostbyDname(input);
    }
}

#endif