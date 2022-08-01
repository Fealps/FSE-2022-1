#include <pthread.h>
#include <signal.h>
#include "config.h"
#include "items.h"

int init = 1;
int main(int argc, char*argv[]) {

    if ((argc < 4) || (argc > 5)) {
		printf("Uso: %s <Numero do cruzamento> <Modo inicial (1-normal 2-modo noturno 3-modo de emergencia)> <ip> <Porta>\n", argv[0]);
		exit(1);
	}

    int cruzamento = atoi(argv[1]);
    
    if(init){
        configPin(cruzamento);
        init--;  
    }

    printf(">> INICIANDO... <<\n");
    switch (atoi(argv[2])){
        case 1:
            modo_normal(atoi(argv[1]));
            break;
        case 2:
            modo_noturno(atoi(argv[1]));
            break;
        case 3:
            modo_emergencia(atoi(argv[1]));
            break;
        default:
            printf(">> Modo Invalido <<\n");
            break;
    }
        
    while(1) {
        sleep(1);
    }

    printf(">> Encerrando... <<\n");
    return 0;
}