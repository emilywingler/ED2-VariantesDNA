# ED2_Grupo <4>_[Emily][Gabrielly][Guilherme][Samuel].zip

all: main

main: main.o arquivos.o fila.o
	gcc -o main main.o arquivos.o fila.o

main.o: main.c arquivos.h fila.h
	gcc -c main.c arquivos.h fila.h

arquivos.o: arquivos.c arquivos.h fila.h
	gcc -c arquivos.c arquivos.h fila.h

fila.o: fila.c fila.h
	gcc -c fila.c fila.h

clean:
	rm -f main main.o arquivos.o fila.o
