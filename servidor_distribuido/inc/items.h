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
void parar(int numero_cruzamento, int numero_semaforo);
void seguir(int numero_cruzamento, int numero_semaforo);
void verdeVermelho(int numero_cruzamento,int numero_semaforo);
void vermelhoVerde(int numero_cruzamento,int numero_semaforo);
void modo_normal(int cruzamento);
void modo_noturno(int cruzamento);
void modo_emergencia(int cruzamento);
void*normalfunc(void * args);
void*intermitente(void * args);
void turnOn(int numero_cruzamento, int  numero_semaforo, int cor_led);
void turnOff(int numero_cruzamento, int  numero_semaforo, int cor_led);

#endif