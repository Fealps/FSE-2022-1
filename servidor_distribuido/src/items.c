#include "items.h"

cruzamento_struct * args = {NULL};

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
        wiringPiISR(botao[cruzamento][i], INT_EDGE_RISING, btnPress);
        pinMode(sensor_passagem[cruzamento][i], INPUT);
        wiringPiISR(sensor_passagem[cruzamento][i], INT_EDGE_BOTH , snsrCatch);
        for(int j= 0; j<2; j++ ){
            pinMode(sensor_velocidade[cruzamento][i][j], INPUT);
        }
    }
}
void btnPress(){}
void snsrCatch(){}
void resetColours(int cruzamento){
    for(int i = 0; i<2; i++){
        for(int j= 0; j<3; j++ ){
            turnOff(cruzamento,i,j);
        }
    }
}




void inicia(int cruzamento, int modo){
    pthread_t socket_cruzamento;
    resetColours(cruzamento);
    args = (cruzamento_struct *)realloc(args, sizeof(cruzamento_struct));
    args->numero_cruzamento = cruzamento;
    args->estado = modo*-1;
    pthread_create(&socket_cruzamento, NULL, &maquinaDeEstado, NULL);
    pthread_detach(socket_cruzamento);
}

void passouVermelho(){

}
void excessoVelocidade(){
}

void*maquinaDeEstado(){
    int estado;
    for(;;){
        estado = args->estado;
        switch (estado){
            case -3:
                printf(">> Modo Emergencia <<\n");
                resetColours(args->numero_cruzamento);
                args->estado = 9;
                break;
            case -2:
                printf(">> Modo Noturno <<\n");
                resetColours(args->numero_cruzamento);
                args->estado=6;
                break;
            case -1:
                printf(">> Modo Normal <<\n");
                resetColours(args->numero_cruzamento);
                turnOn(args->numero_cruzamento,1,2);//R
                turnOn(args->numero_cruzamento,0,2);//R
                args->estado = 0;
            case 0:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,0,1);//Y
                turnOn(args->numero_cruzamento,0,2);//R
                delay(DELAY_MAXIMO);
                args->estado++;
                break;
            case 1:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,1,2);//R
                turnOn(args->numero_cruzamento,1,0);//G
                delay(DELAY_PRINCIPAL_MAXIMO_VERDE);
                args->estado++;
                break;
            case 2:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,1,0);//G
                turnOn(args->numero_cruzamento,1,1);//Y
                delay(DELAY_AMARELO);
                args->estado++;
                break;
            case 3:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,1,1);//Y
                turnOn(args->numero_cruzamento,1,2);//R
                delay(DELAY_MAXIMO);
                args->estado++;
                break;
            case 4:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,0,2);//R
                turnOn(args->numero_cruzamento,0,0);//G
                delay(DELAY_AUXILIAR_MAXIMO_VERDE);
                args->estado++;
                break; 
            case 5:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,0,0);//G
                turnOn(args->numero_cruzamento,0,1);//Y
                delay(DELAY_AMARELO);
                args->estado = 0;
                break;
            case 6:
                printf(">> Estado: %d <<\n",estado);
                turnOn(args->numero_cruzamento,1,1);//Y
                turnOn(args->numero_cruzamento,0,1);//Y
                delay(DELAY_MAXIMO);
                args->estado++;
                break;
            case 7:
                printf(">> Estado: %d <<\n",estado);
                turnOff(args->numero_cruzamento,1,1);//Y
                turnOff(args->numero_cruzamento,0,1);//Y
                delay(DELAY_MAXIMO);
                args->estado=6;
                break;
            case 9:
                printf(">> Estado: %d <<\n",estado);
                turnOn(args->numero_cruzamento,1,0);//G
                turnOn(args->numero_cruzamento,0,2);//R
                args->estado++;
                break;
            case 10:
                break;
            default:
                printf(">> Modo Invalido <<\n");
                args->estado = -1;
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
