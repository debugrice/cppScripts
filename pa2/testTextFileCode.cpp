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
        for (int j = 0; j < 7; j++) {       
        getline(inFile, txtFilearr[i][j], delim);
        }
    }


    // Step 2 Set each variable 
    p[0].setFirstName(txtFilearr[0][0]);
    p[0].setLastName(txtFilearr[0][1]);
    p[0].setMatches(std::stoi(txtFilearr[0][2]));
    p[0].setBalls(std::stoi(txtFilearr[0][3]));
    p[0].setNotOuts(std::stoi(txtFilearr[0][4]));
    p[0].setRuns(std::stoi(txtFilearr[0][5]));
    p[0].printPlayers();


    

}