// Christopher Rice
// 1/24/23
// VS Code Compiler: g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0
// Course Section: CS 221-01
// The following program takes a user prompt of firstname lastname matches runs balls notouts and
// produces a calculation on these inputs using class member methods.

#include "player.h"

int main()
{

    // Variable declaration for user input
    player newplayer;
    string FN;
    string LN;
    float matches;
    float runs;
    float balls;
    float notouts;
    string loopController = "yes";

    // User prompt
    cout << "Welcome to the Cricket player Stats Program." << endl;
    cout << "When prompted, please enter the player's data in the form of" << endl;
    cout << "FirstName LastName Matches Runs Balls NotOuts" << endl;


    // Main function loop - loops until user inputs "no" for testing another player
    while (loopController != "no")
    {

        // User prompt
        cout << "Enter player Data: ";
        cin >> FN >> LN >> matches >> runs >> balls >> notouts;


        // Setting player member variables to user input
        newplayer.setFirstName(FN);
        newplayer.setLastName(LN);
        newplayer.setMatches(matches);
        newplayer.setRuns(runs);
        newplayer.setBalls(balls);
        newplayer.setNotOuts(notouts);

        // The following line outputs player name along with Dismissals, Batting Strike Average and Batting Strike Rate
        // which is calculated inside player class
        cout << newplayer.getFirstName() << " " <<  newplayer.getLastName() <<  " - Dismissals: "<<  newplayer.calcDismissals() <<  " Batting Strike Rate: " <<  newplayer.calcBattingStrikeRate()<<  " Batting Average: " <<  newplayer.calcBattingAverage() << endl;

        // To remove any leftover garbage that may exist inside of the cin input stream
        cin.clear();
	    cin.ignore(100, '\n');

        // The following section is for looping purposes, 
        // if user inputs yes, the loop will continue
        // if the user inputs no, the loop will end
        // if the user inputs anything else, then the input handling section will
        // prompt the user to enter a valid response

        // User prompt
        cout << "Do you wish to test another [yes/no]? " << endl;
        cin >> loopController;

        // Input check loop
        while (loopController!= "yes" && loopController!= "no")
        {
            cin.clear();
	        cin.ignore(100, '\n');
            cout << "Error, Please enter a valid response." << endl;
            cout << "Do you wish to test another [yes/no]? " << endl;
            cin >> loopController;
        }

        // Removes any garbage from input stream
        cin.clear();
	    cin.ignore(100, '\n');
         
    }

    // End of main program
    cout << "Program 1 is completed." << endl;
    return 0;
}