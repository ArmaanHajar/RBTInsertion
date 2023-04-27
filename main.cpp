/*
 * Author: Armaan Hajar
 * Description: Red Black Tree Insertion Code
 * Date: 
 */

#include <iostream>
#include <fstream>

using namespace std;

struct RBTNode {
    int data;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
    bool isRed;
    RBTNode(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
        parent = NULL;
        isRed = true;
    }
};

RBTNode* getParent(RBTNode* node);
RBTNode* getGrandparent(RBTNode* node);
RBTNode* getSibling(RBTNode* node);
RBTNode* getUncle(RBTNode* node);

bool getColor(RBTNode* node);
void RBTInsert(RBTNode* &root, RBTNode* node);
void RBTInsertFix(RBTNode* node);
void RBTPrint(RBTNode* root, int indent);
void rotateLeft(RBTNode* node);
void rotateRight(RBTNode* node);
void replaceNode(RBTNode* oldNode, RBTNode* newNode);
bool isLeftOrRight(RBTNode* node);

int main() {

    char input[10];
    bool running = true;
    RBTNode* root = NULL;

    while (running == true) { // loops until user quits the program
        cout << "------------------------------------------------" << endl;
        cout << "What Would You Like To Do? (ADD/PRINT/READ/HELP)" << endl;

        cin.get(input, 10);
        cin.ignore(1, '\n');

        if (input[0] == 'A' || input[0] == 'a') { // inputs numbers into the tree
            int inputNum;
            cout << "Input a Number Between 1-999" << endl;
            cin >> inputNum;
            cin.ignore(1, '\n');
            if (inputNum >= 1 && inputNum <= 999) { // checks if input is valid
                RBTNode* node = new RBTNode(inputNum);
                RBTInsert(root, node);
                RBTInsertFix(node);
            }
            else { // if input is invalid
                cout << "Invalid Input" << endl;
            }
        }
        else if (input[0] == 'P' || input[0] == 'p') { // prints tree in order
            cout << "Printing Tree" << endl;
            RBTPrint(root, 0);
            cout << endl;
        }
        else if (input[0] == 'R' || input[0] == 'r') { // generates numbers from a file
            cout << "Generating Numbers From File" << endl;
            ifstream numbers;
            numbers.open("numbers.txt");
            int newNum;
            while (numbers >> newNum) {
                cout << "ran" << endl;
                RBTNode* node = new RBTNode(newNum);
                RBTInsert(root, node);
                RBTInsertFix(node);
            }
            numbers.close();
        }
        else if (input[0] == 'H' || input[0] == 'h') { // displays help message
            cout << "ADD: Allows you to input numbers to be added to the tree" << endl;
            cout << "PRINT: Prints the tree in order" << endl;
            cout << "READ: Generates numbers from a file and adds them to the tree" << endl;
            cout << "HELP: Displays this message" << endl;
        }
        else {
            cout << "Sorry, Please Try Again" << endl;
        }
    }
}


RBTNode* getParent(RBTNode* node) {
    return node->parent;
}

RBTNode* getGrandparent(RBTNode* node) {
    return getParent(getParent(node));
}

RBTNode* getSibling(RBTNode* node) {
    RBTNode* parent = getParent(node);
    if (parent == NULL) {
        return NULL;
    }

    if (node == parent->left) {
        return parent->right;
    }
    else {
        return parent->left;
    }
}

RBTNode* getUncle(RBTNode* node) {
    RBTNode* parent = getParent(node);
    RBTNode* grandparent = getGrandparent(node);

    if (grandparent == NULL) {
        return NULL;
    }

    return getSibling(parent);
}

bool getColor(RBTNode* node) {
    if (node == NULL) {
        return false;
    }
    return node->isRed;
}

void RBTInsert(RBTNode* &root, RBTNode* node) {
    if (root == NULL) { // if tree is empty
        root = node;
        root->isRed = false;
    }
    else { // if tree is not empty
        if (node->data < root->data) { // if node is less than root
            if (root->left == NULL) { // if left child is null
                root->left = node;
                node->parent = root;
            }
            else { // if left child is not null
                RBTInsert(root->left, node);
            }
        }
        else { // if node is greater than root
            if (root->right == NULL) { // if right child is null
                root->right = node;
                node->parent = root;
            }
            else { // if right child is not null
                RBTInsert(root->right, node);
            }
        }
    }
}

void RBTInsertFix(RBTNode* node) {
    if (getParent(node) == NULL) { // if node is root
        node->isRed = false;
    }
    else if (getColor(getParent(node)) == false) { // if parent is black
        return;
    }
    else if (getColor(getUncle(node)) == true) { // if uncle is red
        getParent(node)->isRed = false;
        getUncle(node)->isRed = false;
        getGrandparent(node)->isRed = true;
        RBTInsertFix(getGrandparent(node));
    }
    else { // if uncle is black
        RBTNode* parent = getParent(node);
        RBTNode* grandparent = getGrandparent(node);

        if (node == parent->right && parent == grandparent->left) { // if node is right child and parent is left child
            rotateLeft(parent);
            node = node->left;
        }
        else if (node == parent->left && parent == grandparent->right) { // if node is left child and parent is right child
            rotateRight(parent);
            node = node->right;
        }

        parent = getParent(node);
        grandparent = getGrandparent(node);

        if (node == parent->left) { // if node is left child
            rotateRight(grandparent);
        }
        else { // if node is right child
            rotateLeft(grandparent);
        }
        parent->isRed = false;
        grandparent->isRed = true;
    }
}

void RBTPrint(RBTNode* root, int indent) {
    if (root == NULL) { // if the tree is empty
        return;
    }
    indent += 10;

    RBTPrint(root->right, indent); // prints the right side of the tree
    cout << endl;
    for (int i = 10; i < indent; i++) { // prints the indent
        cout << " ";
    }
    cout << root->data;
    if (root->isRed == true) { // prints the color of the node
        cout << " (R)" << endl;
    }
    else {
        cout << " (B)" << endl;
    }
    cout << endl;
    RBTPrint(root->left, indent); // prints the left side of the tree
}

void rotateLeft(RBTNode* node) {
    RBTNode* tempGP = getGrandparent(node);
    RBTNode* tempP = getParent(node);
    RBTNode* tempN = node;
    RBTNode* tempNL = node->left;
    if (node->left == NULL) { // node has no left
        if (isLeftOrRight(node->parent) == true) { // parent is left child of grandparent
            // set nodes parent right to null
            // set nodes grandparent left to null
            // set grandparents left to node
            // set nodes left to parent
            // set parents parent to nodes left
            // set nodes parent to grandparents left
            node->parent->right = NULL;
            tempN->parent->parent->left = NULL;
            tempP->parent->left = node;
            node->left = tempP;
            node->parent = tempGP;
            tempP->parent = node;
            node->parent->left = node;
            node->left = tempP;
        }
        if (isLeftOrRight(node->parent) == false) { // parent is right child of grandparent
            // code
        }
    }
    if (node->left != NULL) { // node has a left
        if (isLeftOrRight(node->parent) == true) { // parent is left child of grandparent
            // code
        }
        if (isLeftOrRight(node->parent) == false) { // parent is right child of grandparent
            // code
        }
    }
}

void rotateRight(RBTNode* node) {
    RBTNode* left = node->left;
    replaceNode(node, left);
    if (node->left != NULL) {
        node->left = left->right;
        if (left->right != NULL) {
            left->right->parent = node;
        }
    }
    left->right = node;
    node->parent = left;
}

void replaceNode(RBTNode* oldNode, RBTNode* newNode) {
    if (oldNode->parent == NULL) {
        newNode->parent = NULL;
    }
    else {
        if (oldNode == oldNode->parent->left) {
            oldNode->parent->left = newNode;
        }
        else {
            oldNode->parent->right = newNode;
        }
    }
}

 bool isLeftOrRight(RBTNode* node) { // checks if node is left or right child
    // returns true if left child
    // returns false is right child
    if (node->parent == NULL) { // if node is root
        return false;
    }
    else if (node->parent->left == node) { // if node is left child
        return true;
    }
    else { // if node is right child
        return false;
    }
 }