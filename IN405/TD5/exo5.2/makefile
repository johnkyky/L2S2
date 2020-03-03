cc = gcc
objets = main.o
flags = -Wall -Werror

all: $(objets)
	gcc $(flags) $(objets)
	./a.out

run:
	./a.out

main.o: main.c
	$(cc) $(flags) -c -o $@ $^


clear:
	rm -f *.o
	rm -f *.out