cc = gcc
objet = main.o
flag = -Wall -Werror -g


prog: $(objet)
	$(cc) $(flag) -o $@ $(objet)
	./$@


run : prog
	./$^


%.o : %.c
	$(cc) -c $(flag) -o $@ $^


clear:
	rm prog *.o