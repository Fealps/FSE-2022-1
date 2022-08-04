#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
int servidorSocket;
int socketCliente;
struct sockaddr_in servidorAddr;
struct sockaddr_in clienteAddr;
unsigned short servidorPorta;
unsigned int clienteLength;
pthread_t socketThread, menuThread;

int vetor[4];
bool log = false;
void sendMessage(char*mensagem);
void *serverSocketThread();
void recebeMensagem();
void * menuInicial();
void handleUser();



int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso: %s <Porta>\n", argv[0]);
		exit(1);
	}
	servidorPorta = atoi(argv[1]);
	if((servidorSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		printf("Falha no Bind\n");

	// Listen
	if(listen(servidorSocket, 10) < 0)
		printf("Falha no Listen\n");		


	pthread_create(&socketThread, NULL, &serverSocketThread, NULL);
    pthread_detach(socketThread);

    pthread_create(&menuThread, NULL,&menuInicial, NULL);
    pthread_detach(menuThread);

	while(1) {
		sleep(1);
	}
	

}
void *serverSocketThread(){
	
	int size = sizeof(socketCliente);
	 /* Aceita conexoes direta entre o servidor e cliente */
	 
    client = accept(server, (struct sockaddr *) &socketCliente, &size);
    if ( (client) == -1 ){
        printf(">> ERRO ao conectar com o Client <<\n");
    } 
    printf(">> Pronto para Começar <<\n");
	recebeMensagem();
}

void recebeMensagem() {
	int retorno_msg;
	while (1) {
		retorno_msg = recv(socketCliente, vetor, 4 * sizeof(int), 0);
		
		if(retorno_msg == 0){
			printf(">> Conexão Encerrada <<\n");
			exit(0);
		}else if(log){ 
			printf(">> Cruzamento: %d << \n", vetor[0]);
			printf("\t\t\tPassagem de carros: %d\n", vetor[1]);
			printf("\t\t\tAcima da velocidade: %d\n", vetor[2]);
			printf("\t\t\tAvanço no vermelho: %d\n", vetor[3]);
			delay(2000);
		}
	}
}

void * menuInicial(){
    printf("\n>>>[MENU]<<<\n");
    printf("[1] Modo Normal\n");
    printf("[2] Modo Noturno\n");
    printf("[3] Modo de Emergencia\n");
	printf("[4] Monitorar\n");
    for(;;){
        handleUser();
    }
}

void handleUser(){
    char mensagem[10];
    bzero(mensagem, 10); /* apaga a informacao*/
            
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0';

	switch(atoi(mensagem)){
		case 1:
			sendMessage("1");
		break;
		case 2:
			sendMessage("2");
		break;
		case 3:
			sendMessage("3");
		break;
		case 4:
			log = true;
		break;
		default:
			printf(">>> Modo invalido <<<\n");
		break;
	}
	menuInicial();
}

void sendMessage(char * mensagem) {
	if(send(socketCliente, mensagem, sizeof(mensagem), 0) < 0){
		perror(">> Falha no envio <<\n");
	} else{
		printf(">> Modo Selecionado <<\n");
	}
}

