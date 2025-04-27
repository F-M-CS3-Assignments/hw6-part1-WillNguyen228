all:
	g++ -Wall -g RedBlackTreeTestsFirstStep.cpp -o rbt

run:
	./rbt
	
try: all run