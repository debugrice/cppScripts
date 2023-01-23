#include "player.cpp"

int main()
{
    playerClass newPlayer;
    string FN;
    string LN;
    int matches;
    int runs;
    int balls;
    int notouts;
    string testSelector = "yes";

    cout << "Welcome to the Cricket Player Stats Program." << endl;
    cout << "When prompted, please enter the player's data in the form of" << endl;
    cout << "FirstName LastName Matches Runs Balls NotOuts" << endl;

    while (testSelector != "no")
    {
        // cout << "Enter Player Data: ";
        cin >> FN >> LN >> matches >> runs >> balls >> notouts;
        cout << "FN: " << FN << endl;
        cout << "LN: " << LN << endl;
        cout << "matches: " << matches << endl;
        cout << "runs: " << runs << endl;
        cout << "balls: " << balls << endl;
        cout << "notouts: " << notouts << endl;


        newPlayer.setFirstName(FN);
        newPlayer.setLastName(LN);
        newPlayer.setMatches(matches);
        newPlayer.setRuns(runs);
        newPlayer.setBalls(balls);
        newPlayer.setNotOuts(notouts);

        cout << "First Name: " << newPlayer.getFirstName() << endl;
        cout << "Not Outs: " << newPlayer.getNotOuts() << endl;

        cout << newPlayer.getFirstName() << " " <<  newPlayer.getLastName() <<  " Dissmissals: "<<  newPlayer.calcDismissals() <<  " Batting Strike Rate: " <<  newPlayer.calcBattingStrikeRate()<<  " Batting Average: " <<  newPlayer.calcBattingStrikeRate();        
        
        cin.clear();
	    cin.ignore(100, '\n');
        
        
        cout << "Do you wish to test another [yes/no]? ";
        cin >> testSelector;
    }


    return 0;
}