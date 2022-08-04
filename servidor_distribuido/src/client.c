#include "client.h"

struct sockaddr_in servidorAddr;
int clienteSocket ;

void RaspConnection(int servidorPorta , char * IP_Servidor) {
    // Criar Socket
    clienteSocket  = socket(AF_INET, SOCK_STREAM, 0);

    if ((clienteSocket  = socket(AF_INET, SOCK_STREAM, 0)) <= 0){ 
       	printf(">> Erro no socket <<\n");
    }
    printf(">> Socket Criado <<\n");

	// Construir struct sockaddr_in
    memset(&servidorAddr, 0, sizeof(servidorAddr)); // Zerando a estrutura de dados
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_addr.s_addr = inet_addr(IP_Servidor); 
    servidorAddr.sin_port = htons(servidorPorta );

    /* Inicia a conexão no socket */
    if(connect(clienteSocket, (struct sockaddr *) &servidorAddr, 
							sizeof(servidorAddr)) < 0){
        perror(">> Não pode conectar no Socket<<\n");
        exit(0);
    }
}

void * clientThread() {
    char mensagem[10];

    while (1) {
        bzero(mensagem, sizeof(mensagem));
        if((recv(clienteSocket, mensagem, sizeof(mensagem), 0)) < 0) {
            printf(">> Não foi possível ler a mensagem enviada <<\n");
        }
        else if (mensagem[0] != '\0'){
            printf(">> Solicitação detectada mudança para o modo >> %s <<\n", mensagem);
            getMessage(mensagem);
        }
    }
}

void sendMensagem(int * mensagem) {
    if (clienteSocket < 0) {
        printf("\nERRO: Não consigo enviar a mensagem!\n");
    }
    int response = send(clienteSocket, mensagem, 4 * sizeof(int), 0);
    if (!response)
        printf("\nERRO: Não foi possivel enviar a mensagem!\n");
}

void getMessage(char * mensagem){

	switch(atoi(mensagem)){
		case 1: 
			printf(">> Selecionado modo 1 <<\n");
			args->estado=-1;
			break;
		case 2:
			printf(">> Selecionado modo 2 <<\n");
            printf("%d", args->estado);
			args->estado=-2;
			break;
		case 3:
			printf(">> Selecionado modo 3 <<\n");
			args->estado=-3;
			break;
		default:
			printf("\n>> Mensagem invalida <<\n");
			args->estado=-1;
		break;
	}
}