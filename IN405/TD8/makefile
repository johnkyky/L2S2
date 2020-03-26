CC = gcc
FLAGS = -Wall -g -Werror
OBJETS = client.o
EXEC = client server million


all: $(EXEC)
	rm -fr /tmp/million


client: client.o
	$(CC) $(FLAGS) -o $@ $<


client.o: client.c
	$(CC) -c $(FLAGS) -o $@ $<


server: server.o
	$(CC) $(FLAGS) -o $@ $<


server.o: server.c
	$(CC) -c $(FLAGS) -o $@ $<


million: million.o
	$(CC) $(FLAGS) -o $@ $<


million.o: million.c
	$(CC) -c $(FLAGS) -o $@ $<


clear:
	rm *.o
	rm $(EXEC)