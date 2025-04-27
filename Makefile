all:
	g++ -Wall -g -c RedBlackTree.cpp
	g++ -Wall -g -c RedBlackTreeTestsFirstStep.cpp
	g++ -Wall -g RedBlackTree.o RedBlackTreeTestsFirstStep.o -o rbt

run:
	./rbt
	
try: all run