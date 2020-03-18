cc = gcc
flags = -Wall -Werror -g
objets = main.o

prog: $(objets)
	$(cc) -o $@ $(flags) $(objets)
	./prog


run:
	./prog


main.o: main.c
	$(cc) -c $(flags) -o $@ $^


clear:
	rm *.o
	rm prog