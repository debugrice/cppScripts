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

    while (testSelector == "yes")
    {
        // cout << "Enter Player Data: ";
        cin >> FN >> notouts;
        // >> LN >> matches >> runs >> balls >>

        newPlayer.setFirstName(FN);
        // newPlayer.setLastName(LN);
        // newPlayer.setMatches(matches);
        // newPlayer.setRuns(runs);
        // newPlayer.setBalls(balls);
        newPlayer.setNotOuts(notouts);

        cout << "First Name: " << newPlayer.getFirstName() << endl;
        cout << "Not Outs: " << newPlayer.getNotOuts() << endl;

        //cout << newPlayer.getFirstName() + " " + newPlayer.getLastName() + " Dissmissals: "+ newPlayer.calcDismissals() + " Batting Strike Rate: " + newPlayer.calcBattingStrikeRate() + " Batting Average: " + newPlayer.calcBattingStrikeRate();        
        
        
        
        cout << "Do you wish to test another [yes/no]? ";
        cin >> testSelector;
    }


    return 0;
}