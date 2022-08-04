#include <pthread.h>
#include <signal.h>
#include "config.h"
#include "items.h"
#include "client.h"

int init = 1;
int main(int argc, char*argv[]) {
    pthread_t socketThread;
    if ((argc < 4) || (argc > 5)) {
		printf("Uso: %s <Numero do cruzamento> <Modo inicial (1-normal 2-modo noturno 3-modo de emergencia)> <ip> <Porta>\n", argv[0]);
		exit(1);
	}

    int cruzamento = atoi(argv[1]);
    int modo = atoi(argv[2]);
    char * ip = argv[3];
    int porta = atoi(argv[4]);
    
    if(init){
        configPin(cruzamento);
        init--;  
    }
    if( modo > 3 || modo < 1 ){
        printf(">> Modo Invalido <<\n");
        return 0;
    }else{
        RaspConnection(porta, ip);
        pthread_create(&socketThread, NULL, &clientThread, NULL);
        pthread_detach(socketThread);
        printf(">> INICIANDO... <<\n");
        inicia(cruzamento, modo);
    }
        
    while(1) {
        sleep(1);
    }

    printf(">> Encerrando... <<\n");
    return 0;
}