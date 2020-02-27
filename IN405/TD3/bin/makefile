all: biblio main.o
	./a.out

biblio: 
	gcc -Werror -Wall -g -c -fPIC io_file.c
	ar rcs libiof.a io_file.o

main_opt.o:
	$ gcc -Wall -Werror -g main_opt.c -L. -liof

main.o:
	$ gcc -Wall -g main.c -L. -liof


clear:
	rm -f a.out *.o libiof.a