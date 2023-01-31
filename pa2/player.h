#include <iostream>
using namespace std;


// player Class Definition
class player {
public:
    string name;
    int score;

    // player Constructor
    player();

    // player Constructor
    player(string newFirstName, string newLastName, float newMatches, float newRuns, float newBalls, float newNotOuts);

    // Public Member Functions Definitions

    // player get functions
    string getFirstName();
    string getLastName();
    float getMatches();
    float getRuns();
    float getBalls();
    float getNotOuts();

    // player set functions
    string setFirstName(string newFirstName);
    string setLastName(string newLastName);
    void setMatches(float newMatches);
    void setRuns(float newRuns);
    void setBalls(float newBalls);
    void setNotOuts(float newNotOuts);

    // These functions are used to calculate stats of the player
    float calcDismissals();
    float calcBattingAverage();
    float calcBattingStrikeRate();

// Private member variables
private:
    string FirstName;
    string LastName;
    float Matches;
    float Runs;
    float Balls;
    float NotOuts;
    float playerarr[4] = {Matches, Runs, Balls, NotOuts};
};


// Constructors method which initializes class variables
player::player()
{
    FirstName = "unknown";
    LastName = "unknown";
    Matches = 0;
    Runs = 0;
    Balls = 0;
    NotOuts = 0;


}

player::player(string newFirstName, string newLastName, float newMatches, float newRuns, float newBalls, float newNotOuts)
{
    FirstName = newFirstName;
    LastName = newLastName;
    Matches = newMatches;
    Runs = newRuns;
    Balls = newBalls;
    NotOuts = newNotOuts;
}


// Returns the player's first name 
string player::getFirstName()
{
    return FirstName;
}

// Returns the player's last name 
string player::getLastName()
{
    return LastName;
}

// Returns the player's matches
float player::getMatches()
{
    return Matches;
}

// Returns the player's runs
float player::getRuns()
{
    return Runs;
}

// Returns the player's balls
float player::getBalls()
{
    return Balls;
}

// Returns the player's not outs
float player::getNotOuts()
{
    return NotOuts;
}

// Sets the first name of the player
string player::setFirstName(string newFirstName)
{
    FirstName = newFirstName;
}

// Sets the last name of the player
string player::setLastName(string newLastName)
{
    LastName = newLastName;

}

// Sets the matches of the player
void player::setMatches(float newMatches)
{
    Matches = newMatches;
}

// Sets the runs of the player
void player::setRuns(float newRuns)
{
    Runs = newRuns;
}

// Sets the balls of the player
void player::setBalls(float newBalls)
{
    Balls = newBalls;
}

// Sets the not outs of the player
void player::setNotOuts(float newNotOuts)
{
    NotOuts = newNotOuts;
}

// The following member function calculates the dismissals of the player
float player::calcDismissals()
{

    return (Matches - NotOuts);
}

// The following member function calculates the batting average of the player
float player::calcBattingAverage()
{
    return (Runs/calcDismissals());
}

// The following member function calculates the batting strike rate of the player
float player::calcBattingStrikeRate()
{
    return (Runs/Balls)*100;
}
