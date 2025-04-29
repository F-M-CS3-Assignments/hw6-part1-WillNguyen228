all:
	g++ -Wall -g -c RedBlackTree.cpp
	# g++ -Wall -g -c RedBlackTreeTestsFirstStep.cpp
	g++ -Wall -g -c RedBlackTreeTests.cpp
	# g++ -Wall -g RedBlackTree.o RedBlackTreeTestsFirstStep.o -o rbt
	g++ -Wall -g RedBlackTree.o RedBlackTreeTests.o -o rbt

	#valgrind --leak-check=full ./rbt

run:
	./rbt
	
try: all run