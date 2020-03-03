CC = gcc
objet = main.o atlacan.o


all: $(objet)
	$(CC) -Wall $^
	./a.out

run:
	./a.out


main.o:	main.c
	$(CC) -c -Wall -o $@ $<


atlacan.o: atlacan.c atlacan.h
	$(CC) -c -o $@ $<


clear:
	rm a.out
	rm *.o