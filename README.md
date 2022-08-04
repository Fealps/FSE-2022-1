# Trabalho 01 de Fundamentos de sistemas embarcados 2022/1

Este trabalho tem por objetivo a criação de um sistema distribuído para o controle e monitoramento de um grupo de sinais de trânsito. O sistema foi desenvolvido para funcionar em um conjunto de placas Raspberry Pi com um servidor central responsável pelo controle e interface com o usuário e servidores distribuídos para o controle local e monitoramento dos sinais do cruzamento junto aos respectivos sensores que monitoram as vias. 

## Rodando

primeiramente compile e rode o servidor usando 
substituindo \<porta> pela porta que deseja usar.
```
$ cd servidor_central
$ make clean && make all
$ make run p=<porta>
```
em seguida rode os servidores 

```
$ cd servidor_distribuido
$ make clean && make all
$ make run cruzamento=<cruzamento> modo= <modo> ip=<ip_server> p=<porta>
```
Substitua o cruzamento pelo numero do cruzamento da placa( 0 ou 1)

Os modos disponiveis são
- 1 Modo Normal - funcionamento padrão do semaforo
- 2 Modo Noturno - luzes amarelas intermitentes
- 3 Modod de emergencia - Via principal aberta e auxiliar fechada

o ip_server é o ip do servidor e a porta é a porta para comunicação.

Alem disso existem os comandos de teste
```
$ cd servidor_distribuido
$ make <normal/noturno/emergencia>
```

no qual a placa roda o respectivo modo no cruzamento 1, no ip164.41.98.17 e na porta 10121

