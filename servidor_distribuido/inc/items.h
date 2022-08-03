#ifndef ITEMS_H
#define ITEMS_H

#include "libs.h"

//DELAY TIMES
#define DELAY_AMARELO                       3000 
#define DELAY_MAXIMO                        1000

#define DELAY_PRINCIPAL_MINIMO_VERDE        10000
#define DELAY_PRINCIPAL_MAXIMO_VERDE        20000
#define DELAY_PRINCIPAL_MINIMO_VERMELHO     5000
#define DELAY_PRINCIPAL_MAXIMO_VERMELHO     10000

#define DELAY_AUXILIAR_MINIMO_VERDE         5000
#define DELAY_AUXILIAR_MAXIMO_VERDE         10000
#define DELAY_AUXILIAR_MINIMO_VERMELHO      10000
#define DELAY_AUXILIAR_MAXIMO_VERMELHO      20000

extern int semaforo [2][2][3];
extern int botao [2][2] ;
extern int sensor_passagem [2][2];
extern int sensor_velocidade [2][2][2];

void configPin(int cruzamento);
void resetColours(int cruzamento);
void inicia(int cruzamento, int modo);
void*maquinaDeEstado(void * args);
void turnOn(int numero_cruzamento, int  numero_semaforo, int cor_led);
void turnOff(int numero_cruzamento, int  numero_semaforo, int cor_led);

#endif