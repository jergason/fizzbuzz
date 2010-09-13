all: test

bst: obj/BST.o
obj/BST.o: BST.h BST.cpp
	g++ -c -o obj/BST.o BST.cpp

ll: obj/LinkedList.o LinkedList.h LinkedList.cpp
	g++ -c -o obj/LinkedList.o LinkedList.cpp
	
test: bst ll colexp passoff
	./colexp part2

clean:
	rm *.o obj/*.o -rf
