#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#ifndef GETHOST_H
#define GETHOST_H


void gethostbyDname(const char* host){
    struct addrinfo hints,*res,*p;
    int status;
    char s[INET6_ADDRSTRLEN];
    memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status == getaddrinfo(host,NULL,&hints,&res)) != 0){
        fprintf(stderr,"getaddrinfo error: %s\n",gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    printf("ip address for host \n\n");

    for (p = res; p != NULL; p = p->ai_next){
        void *addr;
        char *ipver;
        if (p->ai_family == AF_INET){
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }
        else if (p->ai_family == AF_INET6){
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        else{
            continue;
        }
        inet_ntop(p->ai_family,addr,s,sizeof(s));
        printf("%s: %s\n",ipver,s);
    }
    freeaddrinfo(res);
}

#endif