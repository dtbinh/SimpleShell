
shell: hw2.o redirect.o pipes.o
	gcc -Wall -std=c99 hw2.o redirect.o pipes.o -o shell

hw2.o: homework2.c
	gcc -c -Wall -std=c99 homework2.c -o hw2.o

redirect.o: redirect.c
	gcc -c -Wall -std=c99 redirect.c -o redirect.o

pipes.o: pipes.c
	gcc -c -Wall -std=c99 pipes.c -o pipes.o

debug: homework2.c redirect.c pipes.c
	gcc -Wall -g -std=c99 homework2.c pipes.c redirect.c -o hw3debug

clean:
	rm -f *.o hw2 shell hw3debug new
