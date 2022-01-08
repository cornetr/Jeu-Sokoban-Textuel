CC = gcc
CFLAGS = -Wall -c

Sokoban : ./src/main.o ./src/niveau.o ./src/deplacement.o ./src/score.o ./src/historique.o
	$(CC) -o $@ $^

main.o : ./src/main.c ./src/main.h
	$(CC) $(CFLAGS) $<

niveau.o : ./src/niveau.c
	$(CC) $(CFLAGS) $<

deplacement.o : ./src/deplacement.c
	$(CC) $(CFLAGS) $<

score.o : ./src/score.c
	$(CC) $(CFLAGS) $<

historique.o : ./src/historique.c
	$(CC) $(CFLAGS) $<
