#ifndef ESTADO_H
#define ESTADO_H

typedef struct cruzamento_struct{
    int numero_cruzamento;
    int estado;
}cruzamento_struct;

typedef struct mensagem{
    int numero_cruzamento;
    float velocidade_via;
    int qtd_carros;
    int multa_velocidade;
    int multa_vermelho;
}mensagem;


cruzamento_struct * args;

#endif