#include <iostream>
using namespace std;


// Player Class Definition
class playerClass {
public:
    std::string name;
    int score;

    // constructor
    playerClass(std::string n, int s) : name(n), score(s) {}
// Public Member Functions Definitions

// Player Constructor
    playerClass();


// Player get functions
    string getFirstName();
    string getLastName();
    float getMatches();
    float getRuns();
    float getBalls();
    float getNotOuts();

// Player set functions
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
    float Playerarr[4] = {Matches, Runs, Balls, NotOuts};
};


// Constructors method which initializes class variables
playerClass::playerClass()
{
    FirstName = "unknown";
    LastName = "unknown";
    Matches = 0;
    Runs = 0;
    Balls = 0;
    NotOuts = 0;


}


// Returns the player's first name 
string playerClass::getFirstName()
{
    return FirstName;
}

// Returns the player's last name 
string playerClass::getLastName()
{
    return LastName;
}

// Returns the player's matches
float playerClass::getMatches()
{
    return Matches;
}

// Returns the player's runs
float playerClass::getRuns()
{
    return Runs;
}

// Returns the player's balls
float playerClass::getBalls()
{
    return Balls;
}

// Returns the player's not outs
float playerClass::getNotOuts()
{
    return NotOuts;
}

// Sets the first name of the player
string playerClass::setFirstName(string newFirstName)
{
    FirstName = newFirstName;
}

// Sets the last name of the player
string playerClass::setLastName(string newLastName)
{
        LastName = newLastName;

}

// Sets the matches of the player
void playerClass::setMatches(float newMatches)
{
    Matches = newMatches;
}

// Sets the runs of the player
void playerClass::setRuns(float newRuns)
{
    Runs = newRuns;
}

// Sets the balls of the player
void playerClass::setBalls(float newBalls)
{
    Balls = newBalls;
}

// Sets the not outs of the player
void playerClass::setNotOuts(float newNotOuts)
{
    NotOuts = newNotOuts;
}

// The following member function calculates the dismissals of the player
float playerClass::calcDismissals()
{

    return (Matches - NotOuts);
}

// The following member function calculates the batting average of the player
float playerClass::calcBattingAverage()
{
    return (Runs/calcDismissals());
}

// The following member function calculates the batting strike rate of the player
float playerClass::calcBattingStrikeRate()
{
    return (Runs/Balls)*100;
}