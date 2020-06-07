CC = gcc
FLAGS = -g -Wall -Werror -lpthread
OBJ = main.o listPage.o fonction.o fonctionThread.o
EXE = prog


all: $(OBJ)
	$(CC) $(FLAGS) -o prog $(OBJ)
	./$(EXE)


main.o: main.c
	$(CC) $(FLAGS) -c -o $@ $<


listPage.o: listPage.c listPage.h
	$(CC) $(FLAGS) -c -o $@ $<


fonction.o: fonction.c fonction.h
	$(CC) $(FLAGS) -c -o $@ $<


fonctionThread.o: fonctionThread.c fonctionThread.h
	$(CC) $(FLAGS) -c -o $@ $<



clear:
	rm $(EXE)
	rm *.o