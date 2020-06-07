CC = gcc
FLAGS = -lpthread -Wall -g
OBJ = main.o

prog: $(OBJ)
	$(CC) $(FLAGS) -o $@ $^
	./$@

run:
	./prog

main.o : main.c
	$(CC) $(FLAGS) -c -o $@ $<


clear:
	rm *.o
	rm prog