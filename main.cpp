/*
 * Author: Armaan Hajar
 * Description: Red Black Tree Insertion Code
 * Date: 4/28/2023
 * Thank you to Uno Pasadhika for help with the rotateLeft and rotateRight functions
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
void RBTInsertFix(RBTNode* node, RBTNode* root);
void RBTPrint(RBTNode* root, int indent);
void rotateLeft(RBTNode* node, RBTNode* root);
void rotateRight(RBTNode* node, RBTNode* root);

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
                RBTInsertFix(node, root);
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
            while (numbers >> newNum) { // loops until end of file
                RBTNode* node = new RBTNode(newNum);
                RBTInsert(root, node);
                RBTInsertFix(node, root);
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


RBTNode* getParent(RBTNode* node) { // returns the parent of the node
    return node->parent;
}

RBTNode* getGrandparent(RBTNode* node) { // returns the grandparent of the node
    return getParent(getParent(node));
}

RBTNode* getSibling(RBTNode* node) { // returns the sibling of the node
    RBTNode* parent = getParent(node);
    if (parent == NULL) { // if node is root
        return NULL;
    }

    if (node == parent->left) { // if node is left child
        return parent->right;
    }
    else { // if node is right child
        return parent->left;
    }
}

RBTNode* getUncle(RBTNode* node) { // returns the uncle of the node
    RBTNode* parent = getParent(node);
    RBTNode* grandparent = getGrandparent(node);

    if (grandparent == NULL) { // if node is root
        return NULL;
    }

    return getSibling(parent);
}

bool getColor(RBTNode* node) { // returns the color of the node
    if (node == NULL) {
        return false;
    }
    return node->isRed;
}

void RBTInsert(RBTNode* &root, RBTNode* node) { // inserts a node into the tree
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

void RBTInsertFix(RBTNode* node, RBTNode* root) { // fixes the tree after insertion
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
        RBTInsertFix(getGrandparent(node), root);
    }
    else { // if uncle is black
        RBTNode* parent = getParent(node);
        RBTNode* grandparent = getGrandparent(node);

        if (node == parent->right && parent == grandparent->left) { // if node is right child and parent is left child
            rotateLeft(parent, root);
            node = node->left;
        }
        else if (node == parent->left && parent == grandparent->right) { // if node is left child and parent is right child
            rotateRight(parent, root);
            node = node->right;
        }

        parent = getParent(node);
        grandparent = getGrandparent(node);

        if (node == parent->left) { // if node is left child
            rotateRight(grandparent, root);
        }
        else { // if node is right child
            rotateLeft(grandparent, root);
        }
        parent->isRed = false;
        grandparent->isRed = true;
    }
}

void RBTPrint(RBTNode* root, int indent) { // prints the tree
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
    else { // prints the color of the node
        cout << " (B)" << endl;
    }
    cout << endl;
    RBTPrint(root->left, indent); // prints the left side of the tree
}

void rotateLeft(RBTNode* node, RBTNode* root) { // rotates the tree left
    RBTNode* nodeRight = node->right;
    node->right = nodeRight->left;
    if (nodeRight->left != NULL) { // if left child of right child of node is not null
        nodeRight->left->parent = node;
    }
    nodeRight->left = node;
    nodeRight->parent = node->parent;
    if (node->parent == NULL) { // if node is root
        root = nodeRight;
    }
    else if (node == node->parent->left) { // if node is left child
        node->parent->left = nodeRight;
    }
    else { // if node is right child
        node->parent->right = nodeRight;
    } 
    node->parent = nodeRight;
}

void rotateRight(RBTNode* node, RBTNode* root) { // rotates the tree right
    RBTNode* nodeLeft = node->left;
    node->left = nodeLeft->right;
    if (nodeLeft->right != NULL) { // if right child of left child of node is not null
        nodeLeft->right->parent = node;
    }
    nodeLeft->right = node;
    nodeLeft->parent = node->parent;
    if (node->parent == NULL) { // if node is root
        root = nodeLeft;
    }
    else if (node == node->parent->left) { // if node is left child
        node->parent->left = nodeLeft;
    }
    else { // if node is right child
        node->parent->right = nodeLeft;
    }
    node->parent = nodeLeft;
}