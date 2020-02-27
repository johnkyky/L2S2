run: objets/lexc.o objets/cmd.o objets/test_lexc.o
	gcc -Wall -g -o test_lexc objets/test_lexc.o objets/lexc.o objets/cmd.o
	./test_lexc


objets/lexc.o: headers/lexc.h sources/lexc.c
	gcc -Wall -g -o objets/lexc.o -c sources/lexc.c


objets/cmd.o: headers/cmd.h sources/cmd.c
	gcc -Wall -g -o objets/cmd.o -c sources/cmd.c


objets/test_lexc.o: sources/test_lexc.c
	gcc -Wall -g -o objets/test_lexc.o -c sources/test_lexc.c


clear:
	rm -f test_lexc
	rm -f ./objets/*.o