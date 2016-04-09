
shell: hw4.o redirect.o pipes.o
	gcc -Wall -std=c99 hw4.o redirect.o pipes.o -o shell

hw4.o: homework4.c
	gcc -c -Wall -std=c99 homework4.c -o hw4.o

redirect.o: redirect.c
	gcc -c -Wall -std=c99 redirect.c -o redirect.o

pipes.o: pipes.c
	gcc -c -Wall -std=c99 pipes.c -o pipes.o

debug: homework4.c redirect.c pipes.c
	gcc -Wall -g -std=c99 homework4.c pipes.c redirect.c -o hw4debug

clean:
	rm -f *.o shell hw4debug 
