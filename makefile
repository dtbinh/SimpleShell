
shell: hw2.o redirect.o
	g++ -Wall -std=c++11 hw2.o redirect.o -o shell

hw2.o: homework2.cpp
	g++ -c -Wall -std=c++11 homework2.cpp -o hw2.o

redirect.o: redirect.cpp
	g++ -c -Wall -std=c++11 redirect.cpp -o redirect.o

debug: homework2.cpp redirect.cpp
	g++ -Wall -g -std=c++11 homework2.cpp redirect.cpp -o hw3debug

clean:
	rm -f *.o hw2 shell hw2debug new
