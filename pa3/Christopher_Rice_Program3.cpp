// Christopher Rice
// 02/21/2023
// CS 221-01 - Programming Assignment 3

#include "playerList.h"

using namespace std;

int main() {

    // String variables for input by the user
    string playerinputFileName;
    string playeroutputFileName;

    // Program introduction
    cout << "Welcome to the Cricket Player Stats Program. " << endl;
    cout << "This program reads the data from an input file, stores them in a listand then writes the" << endl;
    cout << "result which stores the players dataand stats in the output file." << endl;
    cout << "The input file nameand output file name taken from the user by prompting." << endl;

    // User Prompt
    cout << "Enter input file name : ";
    cin >> playerinputFileName;
    cout << endl;

    cout << "Enter output file name : ";
    cin >> playeroutputFileName;
    cout << endl;

    // Construction of class
    playerList list(playerinputFileName, playeroutputFileName);

    char flag = 'y';
    while (flag == 'y')
    {
        cout << "Would you like to delete a player: y or n." << endl;
        cin >> flag;
        if (flag == 'n')
            break;
        else
        {
            // Initialize string temp variables
            string lastName;
            string firstName;

            // Removal section
            cout << "Who would you like to remove? Enter in firstName lastName format" << endl;
            cin >> firstName >> lastName;
            list.remove(firstName, lastName);

            //// Open the file in append mode
            //ofstream file(playeroutputFileName, ios::app);

            //// Write some data to the file
            //file << "List after removal." << endl;

            //// Close the file
            //file.close();

            // Print List to file
            list.printToFile(playeroutputFileName);
        }
                
    }

    // Final message
    cout << "Program 2 is completed" << endl;
    
    return 0;
}