//Author: Will Nguyen
//Date: 27/04/2025

#include "RedBlackTree.h"
#include <stdexcept> // for exceptions

// Creates an empty tree as default
RedBlackTree::RedBlackTree() {
    root = nullptr;
    numItems = 0; // The tree starts empty!
}

// Creates a tree with a single node (the root)
RedBlackTree::RedBlackTree(int newData) {
    root = new RBTNode();
    root->data = newData;
    root->color = COLOR_BLACK;  // Root should always be black
    root->left = nullptr;
    root->right = nullptr;
    root->parent = nullptr;
    root->IsNullNode = false;   // It's a real node
    numItems = 1;               // Tree has one item
}

// Creates a copy constructor that creates a new red-black tree
RedBlackTree::RedBlackTree(const RedBlackTree &rbt) {
    root = CopyOf(rbt.root);  
}

// Makes a deep copy of a node and its children
RBTNode* RedBlackTree::CopyOf(const RBTNode *node) {
    if (node == nullptr) return nullptr; // Base case: if node is null, return null

    RBTNode* copy = new RBTNode();
    copy->data = node->data;
    copy->color = node->color;
    copy->IsNullNode = node->IsNullNode;
    copy->left = CopyOf(node->left); // Recursively copy left subtree
    copy->right = CopyOf(node->right); // Recursively copy right subtree

    // Parent needs to be set later in the tree structure
    if (copy->left != nullptr) copy->left->parent = copy;
    if (copy->right != nullptr) copy->right->parent = copy;

    return copy;
}


string RedBlackTree::ToPrefixString(const RBTNode *n) {
    if (n == nullptr) return "";  // If the node is null, return an empty string
    // Visit root, then left and right children
    return std::to_string(n->data) + " " + ToPrefixString(n->left) + ToPrefixString(n->right);
}

string RedBlackTree::ToPostfixString(const RBTNode *n) {
    if (n == nullptr) return "";  // If the node is null, return an empty string
    // Visit left and right children, then root
    return ToPostfixString(n->left) + ToPostfixString(n->right) + " " + std::to_string(n->data);
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

bool RedBlackTree::Contains(int data) const {
    RBTNode *node = Get(data);
    return node != nullptr;  // If the node exists, it will not be nullptr
}

int RedBlackTree::GetMin() const {
    if (root == nullptr) {
        throw std::runtime_error("Tree is empty");
    }
    
    RBTNode *current = root;
    while (current->left != nullptr) {
        current = current->left;  // Move to the leftmost node
    }
    return current->data;  // The leftmost node contains the minimum value
}

int RedBlackTree::GetMax() const {
    if (root == nullptr) {
        throw std::runtime_error("Red Black Tree is empty");
    }
    
    RBTNode *current = root;
    while (current->right != nullptr) {
        current = current->right;  // Move to the rightmost node
    }
    return current->data;  // The rightmost node contains the maximum value
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

    // Travel the tree to find the correct position to insert the new node
    while (current != nullptr) {
        parent = current; // Update the current node's parent
        if (node->data < current->data) { // If the new node is less than current node, move left
            if (current->left == nullptr) break; // If there's no left child, we found the spot
            current = current->left; // Otherwise, move to the left child
        } else { // If the new node is more than current node, move right
            //Similar to left
            if (current->right == nullptr) break;
            current = current->right;
        }
    }

    // After finding the correct parent, set the node's parent pointer
    node->parent = parent;

    // Attach the new node to the left or right of the parent, based on its value
    if (node->data < parent->data) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

// This function check red-black tree for violations after insert
void RedBlackTree::InsertFixUp(RBTNode *node) {
    while (node != root && node->parent->color == COLOR_RED) {
        RBTNode *uncle = GetUncle(node);

        if (IsLeftChild(node->parent)) {  // parent is left child
            RBTNode *grandparent = node->parent->parent;
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Case 1: uncle is red -> recolor
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (IsRightChild(node)) {
                    // Case 2: node is right child -> Left Rotate
                    node = node->parent;
                    LeftRotate(node);
                }
                // Case 3: node is left child -> Right Rotate
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                RightRotate(node->parent->parent);
            }
        } else {  // parent is right child
            RBTNode *grandparent = node->parent->parent;
            if (uncle != nullptr && uncle->color == COLOR_RED) {
                // Case 1 mirror: uncle is red -> recolor
                node->parent->color = COLOR_BLACK;
                uncle->color = COLOR_BLACK;
                grandparent->color = COLOR_RED;
                node = grandparent;
            } else {
                if (IsLeftChild(node)) {
                    // Case 2 mirror: node is left child -> Right Rotate
                    node = node->parent;
                    RightRotate(node);
                }
                // Case 3 mirror: node is right child -> Left Rotate
                node->parent->color = COLOR_BLACK;
                node->parent->parent->color = COLOR_RED;
                LeftRotate(node->parent->parent);
            }
        }
    }
    root->color = COLOR_BLACK;
}

// Returns the uncle of a node
RBTNode* RedBlackTree::GetUncle(RBTNode *node) const {
    if (node == nullptr || node->parent == nullptr || node->parent->parent == nullptr) {
        return nullptr;
    }
    if (IsLeftChild(node->parent)) {
        return node->parent->parent->right;
    } else {
        return node->parent->parent->left;
    }
}

// Returns true if node is a left child
bool RedBlackTree::IsLeftChild(RBTNode *node) const {
    return node->parent != nullptr && node->parent->left == node;
}

// Returns true if node is a right child
bool RedBlackTree::IsRightChild(RBTNode *node) const {
    return node->parent != nullptr && node->parent->right == node;
}

// Rotates the node to the left
void RedBlackTree::LeftRotate(RBTNode *node) {
    RBTNode *pivot = node->right;
    if (pivot == nullptr) return; // Safety

    node->right = pivot->left;
    if (pivot->left != nullptr) {
        pivot->left->parent = node;
    }

    pivot->parent = node->parent;
    if (node->parent == nullptr) {
        root = pivot;
    } else if (IsLeftChild(node)) {
        node->parent->left = pivot;
    } else {
        node->parent->right = pivot;
    }

    pivot->left = node;
    node->parent = pivot;
}

// Rotates the node to the right
void RedBlackTree::RightRotate(RBTNode *node) {
    RBTNode *pivot = node->left;
    if (pivot == nullptr) return; // Safety

    node->left = pivot->right;
    if (pivot->right != nullptr) {
        pivot->right->parent = node;
    }

    pivot->parent = node->parent;
    if (node->parent == nullptr) {
        root = pivot;
    } else if (IsRightChild(node)) {
        node->parent->right = pivot;
    } else {
        node->parent->left = pivot;
    }

    pivot->right = node;
    node->parent = pivot;
}

// Search for a node with the given data
RBTNode* RedBlackTree::Get(int data) const {
    RBTNode *current = root;

    while (current != nullptr) {
        if (data == current->data) {
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return nullptr; // Not found
}
