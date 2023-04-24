/*
 * Author: Armaan Hajar
 * Description: Red Black Tree Insertion Code
 * Date: 
 */

#include <iostream>

using namespace std;

int main() {
    char input[10];
    bool running = true;

    while (running == true) { // loops until user quits the program
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "What Would You Like To Do? (ADD/PRINT/READ/HELP)" << endl;

        cin.get(input, 10);
        cin.ignore(1, '\n');

        if (input[0] == 'A' || input[0] == 'a') { // inputs numbers into the tree

        }
        else if (input[0] == 'P' || input[0] == 'p') { // prints tree in order

        }
        else if (input[0] == 'R' || input[0] == 'r') { // generates numbers from a file

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
