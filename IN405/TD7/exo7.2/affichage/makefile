cc = gcc
flags = -Wall -g
objets = affichage.o list.o

affichage: $(objets)
	$(cc) -o $@ $(flags) $(objets)
	./affichage


run:
	./affichage


affichage.o: affichage.c
	$(cc) -c $(flags) -o $@ $<


list.o: list.c list.h
	$(cc) -c $(flags) -o $@ $<


clear:
	rm *.o
	rm affichage