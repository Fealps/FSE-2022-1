#ifndef CONFIG_H
#define CONFIG_H

// Cruzamento 1 e 2
#define SEMAFORO_1_C1_VERDE                 31    //GPIO 1
#define SEMAFORO_1_C1_AMARELO               25    //GPIO 26
#define SEMAFORO_1_C1_VERMELHO              29    //GPIO 21
    
#define SEMAFORO_2_C1_VERDE                 28    //GPIO 20
#define SEMAFORO_2_C1_AMARELO               27    //GPIO 16
#define SEMAFORO_2_C1_VERMELHO              26    //GPIO 12
    
#define BOTAO_PEDESTRE_1_C1                 10    //GPIO 8
#define BOTAO_PEDESTRE_2_C1                 11    //GPIO 7
    
#define SENSOR_PASSAGEM_1_C1                15    //GPIO 14
#define SENSOR_PASSAGEM_2_C1                16    //GPIO 15
    
#define SENSOR_VELOCIDADE_1_A_C1            1     //GPIO 18
#define SENSOR_VELOCIDADE_1_B_C1            4     //GPIO 23
#define SENSOR_VELOCIDADE_2_A_C1            5     //GPIO 24
#define SENSOR_VELOCIDADE_2_B_C1            6     //GPIO 25
    
// Cruzamento 3 e 4 
#define SEMAFORO_1_C2_VERDE                 8     //GPIO 2
#define SEMAFORO_1_C2_AMARELO               9     //GPIO 3
#define SEMAFORO_1_C2_VERMELHO              14    //GPIO 11
    
#define SEMAFORO_2_C2_VERDE                 30     //GPIO 0
#define SEMAFORO_2_C2_AMARELO               21     //GPIO 5
#define SEMAFORO_2_C2_VERMELHO              22     //GPIO 6
    
#define BOTAO_PEDESTRE_1_C2                 12    //GPIO 10
#define BOTAO_PEDESTRE_2_C2                 13    //GPIO 9
    
#define SENSOR_PASSAGEM_1_C2                 7    //GPIO 4
#define SENSOR_PASSAGEM_2_C2                 0    //GPIO 17
    
#define SENSOR_VELOCIDADE_1_A_C2             2    //GPIO 27
#define SENSOR_VELOCIDADE_1_B_C2             3    //GPIO 22
#define SENSOR_VELOCIDADE_2_A_C2            23    //GPIO 13
#define SENSOR_VELOCIDADE_2_B_C2            24    //GPIO 19

int semaforo [2][2][3] =
{
    { //cruzamento 1 
        {
            SEMAFORO_1_C1_VERDE,
            SEMAFORO_1_C1_AMARELO,
            SEMAFORO_1_C1_VERMELHO
        }, //Semaforo 1
        {
            SEMAFORO_2_C1_VERDE,
            SEMAFORO_2_C1_AMARELO,
            SEMAFORO_2_C1_VERMELHO
        }  //Semaforo 2
    },
    { //cruzamento 2
        {
            SEMAFORO_1_C2_VERDE,
            SEMAFORO_1_C2_AMARELO,
            SEMAFORO_1_C2_VERMELHO
        }, //Semaforo 1
        {
            SEMAFORO_2_C2_VERDE,
            SEMAFORO_2_C2_AMARELO,
            SEMAFORO_2_C2_VERMELHO
        }  //Semaforo 2
    }
};

int botao [2][2] =
{
    {BOTAO_PEDESTRE_1_C1,BOTAO_PEDESTRE_2_C1}, //cruzamento 1
    {BOTAO_PEDESTRE_1_C2,BOTAO_PEDESTRE_2_C2} //cruzamento 2
};

int sensor_passagem [2][2] = 
{
    {SENSOR_PASSAGEM_1_C1,SENSOR_PASSAGEM_2_C1}, //cruzamento 1
    {SENSOR_PASSAGEM_1_C2,SENSOR_PASSAGEM_2_C2} //cruzamento 2
};

int sensor_velocidade [2][2][2] = 
{
    { //cruzamento 1
        {SENSOR_VELOCIDADE_1_A_C1,SENSOR_VELOCIDADE_1_B_C1}, //sensor 1
        {SENSOR_VELOCIDADE_2_A_C1,SENSOR_VELOCIDADE_2_B_C1}  //sensor 2
    },
    {//cruzamento 2
        {SENSOR_VELOCIDADE_1_A_C2,SENSOR_VELOCIDADE_1_B_C2}, //sensor 1
        {SENSOR_VELOCIDADE_2_A_C2,SENSOR_VELOCIDADE_2_B_C2}  //sensor 2
    }
};

#endif