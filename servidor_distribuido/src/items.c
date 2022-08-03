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

typedef struct {
    int* numero_cruzamento;
    int* estado;
} cruzamento_struct;

void inicia(int cruzamento, int modo){
    pthread_t socket_cruzamento;
    cruzamento_struct * args;
    args = malloc(sizeof(cruzamento_struct));
    resetColours(cruzamento);
    args->numero_cruzamento = cruzamento;
    args->estado=modo*-1;
    pthread_create(&socket_cruzamento, NULL, &maquinaDeEstado, args);
    pthread_detach(socket_cruzamento);
}

void passouVermelho(){

}
void excessoVelocidade(){

}

void*maquinaDeEstado(void * args){
    cruzamento_struct *args_reais = args;
    int estado = args_reais->estado;
    for(;;){
        switch (estado){
            case -3:
                printf(">> Modo Emergencia <<\n");
                resetColours(args_reais->numero_cruzamento);
                estado = 9;
                break;
            case -2:
                printf(">> Modo Noturno <<\n");
                resetColours(args_reais->numero_cruzamento);
                estado=6;
                break;
            case -1:
                printf(">> Modo Normal <<\n");
                printf(">> Estado: %d <<\n",estado);
                resetColours(args_reais->numero_cruzamento);
                turnOn(args_reais->numero_cruzamento,1,2);
                turnOn(args_reais->numero_cruzamento,0,2);
                estado = 0;
            case 0:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,0,1);//Y
                turnOn(args_reais->numero_cruzamento,0,2);//R
                delay(DELAY_MAXIMO);
                estado++;
                break;
            case 1:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,1,2);//R
                turnOn(args_reais->numero_cruzamento,1,0);//G
                delay(DELAY_PRINCIPAL_MAXIMO_VERDE);
                estado++;
                break;
            case 2:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,1,0);//G
                turnOn(args_reais->numero_cruzamento,1,1);//Y
                delay(DELAY_AMARELO);
                estado++;
                break;
            case 3:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,1,1);//Y
                turnOn(args_reais->numero_cruzamento,1,2);//R
                delay(DELAY_MAXIMO);
                estado++;
                break;
            case 4:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,0,2);//R
                turnOn(args_reais->numero_cruzamento,0,0);//G
                delay(DELAY_AUXILIAR_MAXIMO_VERDE);
                estado++;
                break; 
            case 5:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,0,0);//G
                turnOn(args_reais->numero_cruzamento,0,1);//Y
                delay(DELAY_AMARELO);
                estado = 0;
                break;
            case 6:
                printf(">> Estado: %d <<\n",estado);
                turnOn(args_reais->numero_cruzamento,1,1); // Y
                turnOn(args_reais->numero_cruzamento,0,1); // Y
                delay(DELAY_MAXIMO);
                estado++;
                break;
            case 7:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args_reais->numero_cruzamento,1,1); // Y
                turnOff(args_reais->numero_cruzamento,0,1); // Y
                delay(DELAY_MAXIMO);
                estado=6;
                break;
            case 9:
                printf(">> Estado: %d <<\n",estado);
                turnOn(args_reais->numero_cruzamento,1,0);
                turnOn(args_reais->numero_cruzamento,0,2);
                estado++;
                break;
            case 10:
                break;
            default:
                printf(">> Modo Invalido <<\n");
            break;
        }
    }
}

void turnOn(int numero_cruzamento, int  numero_semaforo, int cor_led){
    digitalWrite(semaforo[numero_cruzamento][numero_semaforo][cor_led], HIGH);
}

void turnOff(int numero_cruzamento, int  numero_semaforo, int cor_led){
    digitalWrite(semaforo[numero_cruzamento][numero_semaforo][cor_led], LOW);
}
