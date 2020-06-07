CC = gcc
FLAGS = -lpthread -Wall -g
OBJ = reduc.o

reduction: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^


reduc.o : reduc.c
	$(CC) $(FLAGS) -c -o $@ $<


clear:
	rm *.o
	rm reduction