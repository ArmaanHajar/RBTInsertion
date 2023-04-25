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
void RBTInsert(RBTNode* root, RBTNode* node);
void RBTInsertFix(RBTNode* node);
void RBTPrint(RBTNode* root, int indent);
void rotateLeft(RBTNode* node);
void rotateRight(RBTNode* node);
void replaceNode(RBTNode* oldNode, RBTNode* newNode);

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

void RBTInsert(RBTNode* root, RBTNode* node) {
    if (root == NULL) {
        root = node;
        root->isRed = false;
    }
    else {
        if (node->data < root->data) {
            if (root->left == NULL) {
                root->left = node;
                node->parent = root;
            }
            else {
                RBTInsert(root->left, node);
            }
        }
        else {
            if (root->right == NULL) {
                root->right = node;
                node->parent = root;
            }
            else {
                RBTInsert(root->right, node);
            }
        }
    }
}

void RBTInsertFix(RBTNode* node) {
    if (getParent(node) == NULL) {
        node->isRed = false;
    }
    else if (getColor(getParent(node)) == false) {
        return;
    }
    else if (getColor(getUncle(node)) == true) {
        getParent(node)->isRed = false;
        getUncle(node)->isRed = false;
        getGrandparent(node)->isRed = true;
        RBTInsertFix(getGrandparent(node));
    }
    else {
        RBTNode* parent = getParent(node);
        RBTNode* grandparent = getGrandparent(node);

        if (node == parent->right && parent == grandparent->left) {
            rotateLeft(parent);
            node = node->left;
        }
        else if (node == parent->left && parent == grandparent->right) {
            rotateRight(parent);
            node = node->right;
        }

        parent = getParent(node);
        grandparent = getGrandparent(node);

        if (node == parent->left) {
            rotateRight(grandparent);
        }
        else {
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
    cout << root->data << endl;
    RBTPrint(root->left, indent); // prints the left side of the tree
}

void rotateLeft(RBTNode* node) {
    RBTNode* right = node->right;
    replaceNode(node, right);
    node->right = right->left;
    if (right->left != NULL) {
        right->left->parent = node;
    }
    right->left = node;
    node->parent = right;
}

void rotateRight(RBTNode* node) {
    RBTNode* left = node->left;
    replaceNode(node, left);
    node->left = left->right;
    if (left->right != NULL) {
        left->right->parent = node;
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