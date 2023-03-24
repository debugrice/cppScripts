#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "playerList.h"


using namespace std;


int main()
{
    player p[5];
    string fileName = "textFile.txt";


    //// Constructor Section
    ifstream inFile(fileName);

    // Number of lines in text file x number of each 
    string txtFilearr[5][6];
    // Components in each line is equal to 6
    char delim = ' ';
    
    // Step 1 - Break each line into components ie chris, rice...
    // Assign each component to a variable, for-loop through each component until a count of 6 is reached then move to the next array in the array of array
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 7; j++) 
        {       
        
            getline(inFile, txtFilearr[i][j], delim);
            cout << "i" << i << endl;
            cout << "j" << j << endl;
            cout << "text file array: " << txtFilearr[i][j] << endl;

            switch (j != 10 ) {
            case 0: p[i].setFirstName(txtFilearr[i][j]);    break;
            case 1: p[i].setLastName(txtFilearr[i][j]);     break;
            case 2: p[i].setMatches(std::stoi(txtFilearr[i][j]));   break;
            case 3: p[i].setBalls(std::stoi(txtFilearr[i][j]));     break;
            case 4: p[i].setNotOuts(std::stoi(txtFilearr[i][j]));   break;
            case 5: p[i].setRuns(std::stoi(txtFilearr[i][j]));  break;
            default: break;
            }

            p[i].printPlayers();
        }
    }
}