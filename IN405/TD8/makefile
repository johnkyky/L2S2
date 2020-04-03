CC = gcc
FLAGS = -Wall -g
OBJETS = client.o
EXEC = .client .server million

DIR_obj = obj/
DIR_src = src/


all: $(EXEC)

.client: $(DIR_obj)client.o
	$(CC) $(FLAGS) -o $@ $<


$(DIR_obj)client.o: $(DIR_src)client.c
	$(CC) -c $(FLAGS) -o $@ $<


.server: $(DIR_obj)server.o
	$(CC) $(FLAGS) -o $@ $<


$(DIR_obj)server.o: $(DIR_src)server.c
	$(CC) -c $(FLAGS) -o $@ $<


million: $(DIR_obj)million.o
	$(CC) $(FLAGS) -o $@ $<


$(DIR_obj)million.o: $(DIR_src)million.c
	$(CC) -c $(FLAGS) -o $@ $<


clear:
	rm $(DIR_obj)*.o
	rm $(EXEC)