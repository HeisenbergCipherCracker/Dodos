#include <stdio.h>
#include <time.h>

#define PROGRAM "DoDos"
#define VERSION "1.0.0"
#define AUTHOR "Seyed Ali Mirmohammad"
#define RELEASE "2024"

//print legal warning

void legal_warning(){
    printf("Usage of %s attacking the targets is illegal and it is a violation of the law.it is user responsibility to obey the federal laws.\n", PROGRAM);
}

//eof


//print version

void print_version(){
    printf("Version: %s\n", VERSION);
    printf("Author: %s\n", AUTHOR);
    printf("Release: %s\n", RELEASE);
}


//defining colors
const char* RED = "\x1b[31m";
const char* GREEN = "\x1b[32m";
const char* BLUE = "\x1b[34m";
const char* MAGENTA = "\x1b[35m";
const char* CYAN = "\x1b[36m";
const char* RESET = "\x1b[0m";
//eof

//defining log messages
const char* ERROR_SIGN = "\x1b[31m[ERROR]%s\x1b[0m\n";
const char* DEBUG_SIGN = "\x1b[34m[DEBUG]\x1b[0m";
const char* WARNING_SIGN = "\x1b[33m[WARNING]\x1b[0m";
const char* CRITICAL_SIGN = "[CRITICAL]";
const char* INFO_SIGN = "\x1b[32m[INFO]%s\x1b[0m\n";

//eof
//defining log functions
//requests
const char* GET = "GET / HTTP/1.1\r\nHost: %s\r\n\r\n";
//eof

//INFO logs messages
const char* SENDING_REQUEST = "Sending GET request to %s";

//eof


//logs

void print_error_msg(const char* msg){
    printf(ERROR_SIGN, msg);
}

void print_inf_message(const char* msg){
    printf(msg,INFO_SIGN);
}

void print_debug_msg(const char* msg){
    printf(DEBUG_SIGN,msg);
}

void print_warning_msg(const char* msg){
    printf(WARNING_SIGN,msg);
}


void print_critical_msg(const char* msg){
    printf(CRITICAL_SIGN,msg);
}
//eof


//defining time settings

void print_time_console(){
    time_t now = time(0);
    char* dt = ctime(&now);
    printf("%s", dt);
}

//eof

//defining colors for console output
void print_black_string(const char* msg){
    printf("\x1b[30m%s\x1b[0m", msg);
}

void print_red_string(const char* msg){
    printf("\x1b[31m%s\x1b[0m", msg);
}

void print_green_string(const char* msg){
    printf("\x1b[32m%s\x1b[0m", msg);
}

void print_yellow_string(const char* msg){
    printf("\x1b[33m%s\x1b[0m", msg);
}

void print_blue_string(const char* msg){
    printf("\x1b[34m%s\x1b[0m", msg);
}

void print_magenta_string(const char* msg){
    printf("\x1b[35m%s\x1b[0m", msg);
}

void print_cyan_string(const char* msg){
    printf("\x1b[36m%s\x1b[0m", msg);
}


//program options
const char* OPTIONS[1000] = {
    "url",
    "port",
    "threads",
    "time",
    "verbose",
    "help"
};

//eof