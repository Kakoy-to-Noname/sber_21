CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

# Targets
all: main

main: tests.o s21_string.o
	$(CC) $(CFLAGS) tests.o s21_string.o -o main -lm

matrix.o: s21_string.c s21_string.h
	$(CC) $(CFLAGS) -c s21_string.c -lm

main.o: tests.c s21_string.h
	$(CC) $(CFLAGS) -c tests.c

clean:
	rm -f *.o main