all: main

main: main.o arquivos.o fila.o
	gcc -o main $^

main.o: main.c arquivos.h fila.h
	gcc -c $<

arquivos.o: arquivos.c arquivos.h fila.h
	gcc -c $<

fila.o: fila.c fila.h
	gcc -c $<

clean:
	rm -f main main.o arquivos.o fila.o

# all: teste

# teste: main.o fila.o
# 	gcc -o teste main.o fila.o

# main.o: main.c fila.h
# 	gcc -c main.c -Wall

# fila.o: fila.c fila.h
# 	gcc -c fila.c -Wall

# clean:
# 	rm main.o fila.o teste
