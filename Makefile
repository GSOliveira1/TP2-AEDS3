CC = gcc
CFLAGS = -Wall -Wextra

all: estrategia1 estrategia2 tp2

estrategia1: estrategia1.o funcoes_estrategia1.o
	$(CC) $(CFLAGS) $^ -o estrategia1

estrategia2: estrategia2.o funcoes_estrategia2.o
	$(CC) $(CFLAGS) $^ -o estrategia2

tp2: tp2.o
	$(CC) $(CFLAGS) $^ -o tp2

estrategia1.o: estrategia1.c estrategia1.h funcoes_estrategia1.c
	$(CC) $(CFLAGS) -c $< -o $@

funcoes_estrategia1.o: funcoes_estrategia1.c estrategia1.h funcoes_estrategia1.c
	$(CC) $(CFLAGS) -c $< -o $@

estrategia2.o: estrategia2.c estrategia2.h funcoes_estrategia2.c
	$(CC) $(CFLAGS) -c $< -o $@

funcoes_estrategia2.o: funcoes_estrategia2.c estrategia2.h funcoes_estrategia2.c
	$(CC) $(CFLAGS) -c $< -o $@

tp2.o: tp2.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o estrategia1 estrategia2 tp2
