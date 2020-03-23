cc = gcc
flags = -Wall -g
objets = envoi.o

envoi: $(objets)
	$(cc) -o $@ $(flags) $(objets)


envoi.o: envoi.c
	$(cc) -c $(flags) -o $@ $<


clear:
	rm *.o
	rm envoi