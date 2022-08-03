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
    int modo = atoi(argv[2]);
    if(init){
        configPin(cruzamento);
        init--;  
    }
    if( modo > 3 || modo < 1 ){
        printf(">> Modo Invalido <<\n");
        return 0;
    }else{
        printf(">> INICIANDO... <<\n");
        inicia(cruzamento, modo);
    }
        
    while(1) {
        sleep(1);
    }

    printf(">> Encerrando... <<\n");
    return 0;
}