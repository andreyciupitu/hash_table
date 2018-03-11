CC=gcc
CFLAGS=-Wall -Wextra -g
LFLAGS=-L . -lhash

build: tema1

tema1: main.o hash_table.o list.o
	$(CC) $^ -o $@ $(LFLAGS)

main.o: main.c hash_table.h utils.h
	$(CC) $(CFLAGS) -c $< -o $@

hash_table.o: hash_table.c hash_table.h utils.h list.h
	$(CC) $(CFLAGS) -c $< -o $@

list.o: list.c utils.h list.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o tema1
