#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int RaspConnection(int argc, char *argv[], char * msg);
#endif