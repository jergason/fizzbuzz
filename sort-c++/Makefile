# /users/ta/cs240ta/bin/sort240test
default: main.o line.o
	g++ -o sort240 main.o line.o -g

main.o: main.cpp line.o
	g++ -c  main.cpp -g

line.o: line.cpp line.h
	g++ -c line.cpp -g

clean:
	rm -f sort240 *.o *.*~


testmain: main.o
	g++ -o sort240 main.o -g

testline: line.cpp line.h main.cpp
	g++ -c line.cpp main.cpp -g
	g++ -o sort240 line.o main.o -g
	
testsort: main.cpp
	g++ -c main.cpp -g
	g++ -o sort240 main.o -g
