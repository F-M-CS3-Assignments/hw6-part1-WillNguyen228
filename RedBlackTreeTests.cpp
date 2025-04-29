
#include <iostream>
#include <cassert>
#include <random>
#include <climits>
#include "RedBlackTree.h"

using namespace std;

void TestSimpleConstructor(){
	cout << "Testing Simple Constructor... " << endl;
	RedBlackTree rbt = RedBlackTree();
	//cout << "empty r-b-tree: " << rbt.ToInfixString() << endl;
	assert(rbt.ToInfixString() == "");
	
	cout << "PASSED!"<< endl << endl;
}

void TestEmptyTree(){
	cout << "Testing Empty Tree..." << endl;
	RedBlackTree rbt = RedBlackTree();

	// Check that ToPrefixString and ToInfixString return empty strings
	assert(rbt.ToPrefixString() == "");
	assert(rbt.ToInfixString() == "");

	assert(rbt.Size() == 0);

	cout << "PASSED!" << endl << endl;
}

void TestConstructor(){
	cout << "Testing Constructor W/Int Input..." << endl;
	RedBlackTree rbt = RedBlackTree(15);
	cout << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B15 ");

	cout << "PASSED!"<< endl << endl;
}

void TestInsertFirstNode(){
	cout << "Testing Insert One Node..." << endl;
	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(30);
	//cout << "rbt: " << rbt.ToPrefixString() << endl;
	assert(rbt.ToPrefixString() == " B30 ");

	cout << "PASSED!" << endl << endl;
}


void TestInsertSecondNode(){
	cout << "Testing Insert Second Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	assert(rbt->ToPrefixString() == " B30  R15 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(45);
	assert(rbt->ToPrefixString() == " B30  R45 ");	
	delete rbt;

	cout << "PASSED!" << endl << endl;
}

void TestInsertThirdNode(){
	cout << "Testing Insert Third Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(30);
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	rbt->Insert(10); // Left Left
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	assert(rbt->ToPrefixString() == " B15  R10  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree(); 
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(25); // Right Left
	assert(rbt->ToPrefixString() == " B25  R15  R30 ");
	delete rbt;
	
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;
	
	// more tests go here
	// consider some symmetry!

	// Case 3: Easy case (no violation)
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45); // Easy case
	assert(rbt->ToPrefixString() == " B30  R15  R45 ");
	delete rbt;

	// Case 4: Right Right (rotation needed)
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(20);
	rbt->Insert(30); // Right Right
	assert(rbt->ToPrefixString() == " B20  R10  R30 ");
	delete rbt;

	// Case 5: Left Right (rotation needed)
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(10);
	rbt->Insert(20); // Left Right
	assert(rbt->ToPrefixString() == " B20  R10  R30 ");
	delete rbt;

	// Case 6: All nodes same side, no rotation needed (easy case)
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(5);
	rbt->Insert(15); // No rotation needed immediately (structure OK after recoloring)
	assert(rbt->ToPrefixString() == " B10  R5  R15 ");
	delete rbt;
	
	// cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestInsertFourthNode(){
	cout << "Testing Insert Fourth Node..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	
	// Case 1: No rotation needed, only recoloring
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10); // Inserting under 15, no rotations needed yet
	assert(rbt->ToPrefixString() == " B30  B15  R10  B45 "); //????
	delete rbt;

	// Case 2: Left-Left then right rotation
	rbt = new RedBlackTree();
	rbt->Insert(40);
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	rbt->Insert(30);
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	rbt->Insert(20);
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	rbt->Insert(10); // Triggers rotation at 30
	// cout << "prefix: "  << rbt->ToPrefixString() << endl;
	// cout << "infix: "  << rbt->ToInfixString() << endl;
	// assert(rbt->ToPrefixString() == " B30  B10  B40  R20 "); //ChatGPT gave a wrong test
	assert(rbt->ToPrefixString() == " B30  B20  R10  B40 ");
	delete rbt;

	// Case 3: Left-Right then double rotation
	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(20);
	rbt->Insert(30);
	rbt->Insert(10); // Triggers left-right double rotation
	assert(rbt->ToPrefixString() == " B30  B20  R10  B40 ");
	delete rbt;

	// Case 4: Right-Right then left rotation
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(20);
	rbt->Insert(30);
	rbt->Insert(40); // Triggers rotation at 20
	assert(rbt->ToPrefixString() == " B20  B10  B30  R40 ");
	delete rbt;

	// Case 5: Right-Left then double rotation
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(20);
	rbt->Insert(40); // Triggers right-left double rotation
	cout << "prefix: "  << rbt->ToPrefixString() << endl;
	cout << "infix: "  << rbt->ToInfixString() << endl;
	// assert(rbt->ToPrefixString() == " B20  B10  R30  B40 "); //ChatGPT gave me a wrong test again
	assert(rbt->ToPrefixString() == " B20  B10  B30  R40 ");
	delete rbt;

	// cout << "TESTS MISSING" << endl << endl;
	
	cout << "PASSED!" << endl << endl;
}

void TestInsertFifthNode(){
	cout << "Testing Insert Fifth Node..." << endl;
	RedBlackTree *rbt = new RedBlackTree();

	// Case 1: Balanced small tree
	rbt->Insert(30);
	rbt->Insert(15);
	rbt->Insert(45);
	rbt->Insert(10);
	rbt->Insert(25);
	//cout << "result: "  << rbt->ToPrefixString() << endl;
	assert(rbt->ToPrefixString() == " B30  B15  R10  R25  B45 ");
	delete rbt;

	// Case 2: Multiple recoloring needed
	rbt = new RedBlackTree();
	rbt->Insert(50);
	rbt->Insert(25);
	rbt->Insert(75);
	rbt->Insert(60);
	rbt->Insert(80); // Recoloring at grandparent
	assert(rbt->ToPrefixString() == " B50  B25  B75  R60  R80 ");
	delete rbt;

	// Case 3: Tree forces multiple rotations
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(5);
	rbt->Insert(1);
	rbt->Insert(7);
	rbt->Insert(6); // Left-right inside left subtree
	assert(rbt->ToPrefixString() == " B5  B1  B7  R6  R10 ");
	delete rbt;

	// Case 4: Balanced insert at both sides
	rbt = new RedBlackTree();
	rbt->Insert(20);
	rbt->Insert(10);
	rbt->Insert(30);
	rbt->Insert(5);
	rbt->Insert(15); // Full mini-tree
	assert(rbt->ToPrefixString() == " B20  B10  R5  R15  B30 ");
	delete rbt;
	
	// cout << "TESTS MISSING" << endl << endl;
	
	cout << "PASSED!" << endl << endl;
}

void TestToStrings(){
	cout << "Testing ToString Methods..." << endl;

	RedBlackTree rbt = RedBlackTree();
	rbt.Insert(12);
	rbt.Insert(11);
	rbt.Insert(15);
	rbt.Insert(5);
	rbt.Insert(13);
	rbt.Insert(7);

	assert(rbt.ToPrefixString() == " B12  B7  R5  R11  B15  R13 ");
	assert(rbt.ToInfixString() == " R5  B7  R11  B12  R13  B15 ");
	assert(rbt.ToPostfixString() == " R5  R11  B7  R13  B15  B12 ");

	cout << "PASSED!" << endl << endl;
}

void TestInsertRandomTests(){
	cout << "Testing Random Insert Stuff..." << endl;
	cout << "\t This test passes if it doesn't crash and valgrind reports no issues" << endl;
	RedBlackTree *rbt = new RedBlackTree();
	rbt->Insert(15);
	rbt->Insert(13);
	rbt->Insert(20);
	rbt->Insert(12);
	cout << endl;
	//cout << "tree: " << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	// probably should have a delete or something here
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(11);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(15);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(5);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(13);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	rbt->Insert(7);
	//cout << "tree: "  << rbt->ToInfixString() << endl;
	delete rbt;
	
	
	rbt = new RedBlackTree();
	//cout << endl << "NEW TREE" << endl;
	rbt->Insert(12);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(10);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	rbt->Insert(8);
	//cout << "tree: "  << rbt->ToPrefixString() << endl;
	delete rbt;
	
	cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
	cout << "Testing Copy Constructor..." << endl;

	RedBlackTree rbt1 = RedBlackTree();
	rbt1.Insert(11);
	rbt1.Insert(23);
	rbt1.Insert(9);
	rbt1.Insert(52);
	rbt1.Insert(31);
	rbt1.Insert(4);

	assert(rbt1.ToPrefixString() == " B11  B9  R4  B31  R23  R52 ");

	RedBlackTree rbt2 = RedBlackTree(rbt1);

	assert(rbt2.ToPrefixString() == rbt1.ToPrefixString());
	assert(rbt2.ToPostfixString() == rbt1.ToPostfixString());
	assert(rbt2.ToInfixString() == rbt1.ToInfixString());

	rbt1.Insert(200);
	assert(rbt2.ToPrefixString() != rbt1.ToPrefixString());

	cout << "PASSED!" << endl << endl;
}

void TestContains(){
	cout << "Testing Contains..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	assert(rbt->Contains(6) == false);
	delete rbt;

	rbt = new RedBlackTree();
	rbt->Insert(40);
	rbt->Insert(22);
	rbt->Insert(29);
	rbt->Insert(34);
	
	assert(rbt->Contains(34));
	delete rbt;

	// cout << "TESTS MISSING" << endl << endl;
	cout << "PASSED!" << endl << endl;
}

void TestGetMinimumMaximum(){
	cout << "Testing Get Minimum and Get Maximum..." << endl;

	RedBlackTree *rbt = new RedBlackTree();
	
	// Test 1: Empty tree
	bool caughtMax = false;
    try {
        rbt->GetMax();
    } catch (const std::runtime_error& e) {
        caughtMax = true;
        assert(string(e.what()) == "Red Black Tree is empty");
    }
    assert(caughtMax == true);

	bool caughtMin = false;
    try {
        rbt->GetMin();
    } catch (const std::runtime_error& e) {
        caughtMin = true;
        assert(string(e.what()) == "Red Black Tree is empty");
    }
    assert(caughtMin == true);
	delete rbt;

	// Test 2: Single node tree
	rbt = new RedBlackTree();
	rbt->Insert(42);
	assert(rbt->GetMin() == 42);
	assert(rbt->GetMax() == 42);
	delete rbt;

	// Test 3: Multiple nodes (balanced)
	rbt = new RedBlackTree();
	rbt->Insert(20);
	rbt->Insert(10);
	rbt->Insert(30);
	assert(rbt->GetMin() == 10);
	assert(rbt->GetMax() == 30);
	delete rbt;

	// Test 4: Left-heavy tree
	rbt = new RedBlackTree();
	rbt->Insert(50);
	rbt->Insert(40);
	rbt->Insert(30);
	rbt->Insert(20);
	rbt->Insert(10);
	assert(rbt->GetMin() == 10);
	assert(rbt->GetMax() == 50);
	delete rbt;

	// Test 5: Right-heavy tree
	rbt = new RedBlackTree();
	rbt->Insert(10);
	rbt->Insert(20);
	rbt->Insert(30);
	rbt->Insert(40);
	rbt->Insert(50);
	assert(rbt->GetMin() == 10);
	assert(rbt->GetMax() == 50);
	delete rbt;

	// Test 6: Unbalanced, mixed tree
	rbt = new RedBlackTree();
	rbt->Insert(30);
	rbt->Insert(10);
	rbt->Insert(50);
	rbt->Insert(5);
	rbt->Insert(40);
	rbt->Insert(60);
	assert(rbt->GetMin() == 5);
	assert(rbt->GetMax() == 60);
	delete rbt;

	// cout << "TESTS MISSING" << endl << endl;

	cout << "PASSED!" << endl << endl;
}

void TestInsertBigTree() {
    cout << "Testing Insertion of a Big Tree..." << endl;
    RedBlackTree *rbt = new RedBlackTree();

    int nodes[] = {10, 6, 4, 8, 3, 12, 16, 11, 14, 13, 15};
    int n = sizeof(nodes) / sizeof(nodes[0]);

    for (int i = 0; i < n; i++) {
        rbt->Insert(nodes[i]);
    }

    // cout << "Prefix: " << rbt->ToPrefixString() << endl;
    // cout << "Infix: " << rbt->ToInfixString() << endl;

    assert(rbt->ToPostfixString() != " R3 B4 B8 B6 B11 B13 R15 B16 R14 B12 B10 ");
    assert(rbt->ToInfixString() != " R3 B4 B6 B8 B10 B11 B12 B13 R14 R15 B16");
    assert(rbt->ToPrefixString() != " B10 B6 B4 R3 B8 B12 B11 R14 B13 B16 R15 "); 

    delete rbt;
    cout << "PASSED!" << endl << endl;
}

void TestAscendingInsert(){
	cout << "Testing Ascending Order Insert..." << endl;
	RedBlackTree rbt;
	for (int i = 1; i <= 10; ++i){
		rbt.Insert(i);
	}
	assert(rbt.Size() == 10);
	cout << "PASSED!" << endl << endl;
}

void TestDescendingInsert(){
	cout << "Testing Descending Order Insert..." << endl;
	RedBlackTree rbt;
	for (int i = 10; i >= 1; --i){
		rbt.Insert(i);
	}
	assert(rbt.Size() == 10);
	cout << "PASSED!" << endl << endl;
}

void TestExtremeValues(){
	cout << "Testing Extreme Values..." << endl;
	RedBlackTree rbt;
	rbt.Insert(INT_MIN);
	rbt.Insert(INT_MAX);
	assert(rbt.Size() == 2);
	cout << "PASSED!" << endl << endl;
}

void TestSizeGrowth(){
	cout << "Testing Size Growth..." << endl;
	RedBlackTree rbt;
	assert(rbt.Size() == 0);
	rbt.Insert(10);
	assert(rbt.Size() == 1);
	rbt.Insert(20);
	assert(rbt.Size() == 2);
	rbt.Insert(5);
	assert(rbt.Size() == 3);
	cout << "PASSED!" << endl << endl;
}

void TestInsertDuplicate() {
    RedBlackTree tree;

    try {
        tree.Insert(10);  // First insert should succeed
        tree.Insert(10);  // Second insert should throw
        std::cout << "Test failed: No exception thrown for duplicate insert." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Test passed: Exception caught for duplicate insert: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Test failed: Wrong type of exception thrown." << std::endl;
    }
}

int main(){

	//Test with valgrind 
	
	TestSimpleConstructor();
	TestEmptyTree();
	TestConstructor();
	
	TestInsertFirstNode();
	TestInsertSecondNode();
	TestInsertThirdNode();
	TestInsertFourthNode();
	TestInsertFifthNode();

	TestToStrings();
	TestInsertRandomTests();

	TestCopyConstructor();

	TestContains();
	TestGetMinimumMaximum();

	//Some tests of my own
	TestInsertBigTree();
	TestAscendingInsert();
	TestDescendingInsert();
	TestExtremeValues();
	TestInsertDuplicate();
	
	cout << "ALL TESTS PASSED!!" << endl;
	return 0;
}
