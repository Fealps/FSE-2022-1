# Executable
BINFOLDER := bin/
# .hppz
INCFOLDER := inc/
# .c
SRCFOLDER := src/
# .o
OBJFOLDER := obj/
CC := gcc
CFLAGS := -W -Wall -ansi -lwiringPi -lpthread  -std=gnu11 -Wimplicit-function-declaration -Wunused-parameter 
SRCFILES := $(wildcard src/*.c)

all: $(SRCFILES:src/%.c=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/prog 
obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc
run: bin/prog 
	bin/prog $(cruzamento) $(modo) $(ip) $(p)
.PHONY: clean

clean:
	rm -rf obj/*
	rm -rf bin/*

normal:	
	make clean 
	make all 
	clear
	make run cruzamento=1 modo=1 ip=164.41.98.17 p=10121 

noturno:	
	make clean 
	make all 
	clear
	make run cruzamento=1 modo=2 ip=164.41.98.17 p=10121 
emergencia:
	make clean 
	make all 
	clear
	make run cruzamento=1 modo=3 ip=164.41.98.17 p=10121

