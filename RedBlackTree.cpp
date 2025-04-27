//Author: Will Nguyen
//Date: 27/04/2025

#include "RedBlackTree.h"
#include <stdexcept> // for exceptions

// Creates an empty tree as default
RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0; // The tree starts empty!
}

// Helper function to print Infix traveral order
// Infix = left subtree -> current node -> right subtree
string RedBlackTree::ToInfixString(const RBTNode *n) {
    if (n == nullptr || n->IsNullNode) {
        return ""; // Null or empty node, return empty string
    }

    string result = "";

    if (n->left != nullptr) {
        result += ToInfixString(n->left);
    }

    result += GetNodeString(n);

    if (n->right != nullptr) {
        result += ToInfixString(n->right);
    }

    return result;
}

// Convert node's data and color into string
string RedBlackTree::GetNodeString(const RBTNode *n) {
    // If the node is empty, return an empty space
    if (n == nullptr || n->IsNullNode) {
        return "";
    }

    // Format: [color][value] i.e. B5, R7
    string result = " " + GetColorString(n) + to_string(n->data) + " ";
    // cout << result << endl;
    return result;
}

// Get color for a node
string RedBlackTree::GetColorString(const RBTNode *n) {
    if (n == nullptr) {
        return "";
    }

    switch (n->color) {
        case COLOR_RED:
            return "R";
        case COLOR_BLACK:
            return "B";
        case COLOR_DOUBLE_BLACK:
            return "DB"; // Will be used for delete operations later
        default:
            return "?"; // Unknown color
    }
}

void RedBlackTree::Insert(int newData) {
    // Create a new node using the struct
    RBTNode* newNode = new RBTNode();
    newNode->data = newData;
    newNode->color = COLOR_RED;  // new nodes are red by default in Red Black Trees

    // Insert it into the tree
    BasicInsert(newNode);

    // Fix any Red-Black Tree property violations
    // InsertFixUp(newNode);

    // Update the number of items
    numItems++;
}

// BasicInsert just inserts like a regular BST
void RedBlackTree::BasicInsert(RBTNode *node) {
    if (root == nullptr) {
        root = node; // Assigning the node as the root of one doesn't exist
        node->color = COLOR_BLACK; // Root must always be black
        return;
    }

    RBTNode *current = root;
    RBTNode *parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (node->data < current->data) {
            if (current->left == nullptr) break;
            current = current->left;
        } else {
            if (current->right == nullptr) break;
            current = current->right;
        }
    }

    node->parent = parent;
    if (node->data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}
