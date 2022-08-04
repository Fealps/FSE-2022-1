#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

struct sockaddr_in servidorAddr;
struct sockaddr_in clienteAddr;
unsigned short servidorPorta;
unsigned int clienteLength;
pthread_t socketThread[4], menuThread;
char menssagemServer[20] = "";
int vetor[4];
bool log = false;
bool msgSend = false;
void sendMessage(int client);
void *serverSocketThread();
void *recebeMensagem(void*args);
void *menuInicial();
void handleUser();

typedef struct thread_args{
	char * server_ip;
	int porta;
	int client;
	int server;
}thread_args;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Uso: %s <Porta>\n", argv[0]);
		exit(1);
	}

	thread_args * args[4];

	for(int i=0; i<4;i++){
		args[i] = malloc(sizeof(thread_args));
    	args[i]->porta = atoi(argv[1]) + i;
		pthread_create(&socketThread[i], NULL, &serverSocketThread, args[i]);
    	pthread_detach(socketThread[i]);
	}

    pthread_create(&menuThread, NULL,&menuInicial, NULL);
    pthread_detach(menuThread);

	while(1) {
		sleep(1);
	}
	

}
void *serverSocketThread(void*args){
	thread_args *actual_args = args;
	int socketCliente;
	int servidorSocket;
	pthread_t msgThread;

	servidorPorta = actual_args->porta;

	if((servidorSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		printf("falha no socker do Servidor\n");

	// Montar a estrutura sockaddr_in
	memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
	servidorAddr.sin_family = AF_INET;
	servidorAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servidorAddr.sin_port = htons(servidorPorta);

	// Bind
	if(bind(servidorSocket, (struct sockaddr *) &servidorAddr, sizeof(servidorAddr)) < 0)
		perror("Falha no Bind\n");

	// Listen
	if(listen(servidorSocket, 10) < 0) {
		perror("[SERVER] Não é possivel escutar server socket\n");
		exit(1);
	}
	int size = sizeof(clienteAddr);
  	socketCliente = accept(servidorSocket, (struct sockaddr *) &clienteAddr, &size);
    if ( (socketCliente) == -1 ){
        perror(">> ERRO ao conectar com o Client <<\n");
    } else{
    	printf(">> Pronto para Começar <<\n");

	}

	actual_args->client = socketCliente;
	actual_args->server = servidorSocket;

	pthread_create(&msgThread, NULL, &recebeMensagem, actual_args);
    pthread_detach(msgThread);
	sendMessage(socketCliente);
}

void* recebeMensagem(void*args) {
	thread_args *actual_args = args;
	int retorno_msg;
	int socketCliente = actual_args->client;

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
			strcpy(menssagemServer, mensagem);
			msgSend = true;
		break;
		case 2:
			strcpy(menssagemServer, mensagem);
			msgSend = true;
		break;
		case 3:
			strcpy(menssagemServer, mensagem);
			msgSend = true;
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

void sendMessage(int client) {
	while(1){
		if(msgSend){
			if(send(client, menssagemServer, sizeof(menssagemServer), 0) < 0){
				printf(">> Falha no envio <<\n");
			} else{
				printf(">> Modo Selecionado <<\n");
			}
			msgSend = false;
		}
	}
}

