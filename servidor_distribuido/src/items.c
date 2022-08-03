#include "items.h"


void configPin(int cruzamento){
    printf(">> Configurando... <<\n");
    wiringPiSetup();
    for(int i = 0; i<2; i++){
        for(int j= 0; j<3; j++ ){
            pinMode(semaforo[cruzamento][i][j], OUTPUT);
            turnOff(cruzamento,i,j);
        }
        
    }
    for(int i = 0; i<2; i++){
        pinMode(botao[cruzamento][i], INPUT);
        pinMode(sensor_passagem[cruzamento][i], INPUT);
        for(int j= 0; j<2; j++ ){
            pinMode(sensor_velocidade[cruzamento][i][j], INPUT);
        }
    }
}

void resetColours(int cruzamento){
    for(int i = 0; i<2; i++){
        for(int j= 0; j<3; j++ ){
            turnOff(cruzamento,i,j);
        }
    }
}

void parar(int numero_cruzamento, int numero_semaforo){
    int timeON = 100;
    int timeMin = 500;
    if(1){ 
        verdeVermelho(numero_cruzamento,numero_semaforo);
    }else{
        //delay(timeMin-timeON);
        verdeVermelho(numero_cruzamento,numero_semaforo);
    }
}

void seguir(int numero_cruzamento, int numero_semaforo){
    vermelhoVerde(numero_cruzamento, numero_semaforo);
}

void verdeVermelho(int numero_cruzamento,int numero_semaforo){
    turnOff(numero_cruzamento,numero_semaforo,0);   //desliga verde
    turnOn(numero_cruzamento,numero_semaforo,1);    //liga amarelo
    delay(DELAY_AMARELO);                           //delay 3 seg
    turnOff(numero_cruzamento,numero_semaforo,1);   //desliga amarelo
    turnOn(numero_cruzamento,numero_semaforo,2);    //liga vermelho
    delay(DELAY_MAXIMO);
}

void vermelhoVerde(int numero_cruzamento,int numero_semaforo){
    turnOff(numero_cruzamento,numero_semaforo,2);   //desliga vermelho
    turnOn(numero_cruzamento,numero_semaforo,0);    //liga verde
}

typedef struct {
    int* numero_semaforo;
    int* numero_cruzamento;
} cruzamento_struct;

void modo_normal(int cruzamento){
    printf(">> Modo Normal <<\n");
    int i;
    pthread_t socket_cruzamento[2];
    cruzamento_struct * args[2] ;

    for(i = 0; i <2; ++i){
        args[i] = malloc(sizeof(cruzamento_struct));
    }

    resetColours(cruzamento);
    for( i = 0; i <2; ++i){
        args[i]->numero_semaforo = i;
        args[i]->numero_cruzamento = cruzamento;
        pthread_create(&socket_cruzamento[i], NULL, &normalfunc, args[i]);
        pthread_detach(socket_cruzamento[i]);
    }
}

void passouVermelho(){

}
void excessoVelocidade(){

}

void*normalfunc(void * args){
    cruzamento_struct *args_reais = args;
    for(;;){
        if(args_reais->numero_semaforo == 1){
            delay(DELAY_AMARELO);
            seguir(args_reais->numero_cruzamento,args_reais->numero_semaforo);
            printf(">> Semaforo Principal: Verde <<\n");
            delay(DELAY_PRINCIPAL_MAXIMO_VERDE);
            parar(args_reais->numero_cruzamento,args_reais->numero_semaforo);
            printf(">> Semaforo Principal: Vermelho <<\n");
            delay(DELAY_PRINCIPAL_MAXIMO_VERMELHO);
        }else{
            parar(args_reais->numero_cruzamento,args_reais->numero_semaforo);
            printf(">> Semaforo Auxiliar: Vermelho <<\n");
            delay(DELAY_AUXILIAR_MAXIMO_VERMELHO);
            delay(DELAY_AMARELO);
            seguir(args_reais->numero_cruzamento,args_reais->numero_semaforo);
            printf(">> Semaforo Auxiliar: Verde <<\n");
            delay(DELAY_AUXILIAR_MAXIMO_VERDE);
        }
    }
}


void modo_noturno(int cruzamento){
    printf(">> Modo Noturno <<\n");
    int i;
    pthread_t socket_cruzamento[2];
    cruzamento_struct * args[2] ;

    for(i = 0; i <2; ++i){
        args[i] = malloc(sizeof(cruzamento_struct));
    }
    resetColours(cruzamento);
    for( i = 0; i <2; ++i){
        args[i]->numero_semaforo = i;
        args[i]->numero_cruzamento = cruzamento;
        pthread_create(&socket_cruzamento[i], NULL, &intermitente, args[i]);
        pthread_detach(socket_cruzamento[i]);
    }

}

void modo_emergencia(int cruzamento){
    printf(">> Modo Emergencia <<\n");
    resetColours(cruzamento);
    turnOn(cruzamento,1,0);
    turnOn(cruzamento,0,2);
    
}

void* intermitente(void *args){

    cruzamento_struct *args_reais = args;
    // thread --- essa func
                                     //delay 3 seg
    for(;;){
        turnOn(args_reais->numero_cruzamento,args_reais->numero_semaforo,1);    //liga amarelo
        delay(800);   
        //while(timeday > meia_noite && timeday < cinco_am){
        turnOff(args_reais->numero_cruzamento,args_reais->numero_semaforo,1);   //desliga amarelo
        delay(800);  
    }
 
}

void turnOn(int numero_cruzamento, int  numero_semaforo, int cor_led){
    digitalWrite(semaforo[numero_cruzamento][numero_semaforo][cor_led], HIGH);
}

void turnOff(int numero_cruzamento, int  numero_semaforo, int cor_led){
    digitalWrite(semaforo[numero_cruzamento][numero_semaforo][cor_led], LOW);
}
