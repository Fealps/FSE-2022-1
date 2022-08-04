#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <strings.h> 
#include <ctype.h>
#include "estado.h"

void RaspConnection(int servidorPorta , char * IP_Servidor);
void * clientThread();
void sendMensagem(int * mensagem);
void getMessage(char * mensagem);

#endif