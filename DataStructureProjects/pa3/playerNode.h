#include <iostream>
using namespace std;


// playerNode Class Definition
class playerNode {
public:
    string name;
    int score;

    // playerNodeNode Constructor
    playerNode();

    // playerNode Constructor
    playerNode(string newFirstName, string newLastName, float newMatches, float newRuns, float newBalls, float newNotOuts);

    // Public Member Functions Definitions

    // playerNode get functions
    string getFirstName();
    string getLastName();
    float getMatches();
    float getRuns();
    float getBalls();
    float getNotOuts();

    // playerNode set functions
    void setFirstName(string newFirstName);
    void setLastName(string newLastName);
    void setMatches(float newMatches);
    void setRuns(float newRuns);
    void setBalls(float newBalls);
    void setNotOuts(float newNotOuts);

    // These functions are used to calculate stats of the playerNode
    float calcDismissals();
    float calcBattingAverage();
    float calcBattingStrikeRate();

    void printplayerNodes();

    // Program 3 Additions
    // Sequential node initialization
    playerNode* prev = nullptr;
    playerNode* next = nullptr;



// Private member variables
private:
    string FirstName;
    string LastName;
    float Matches;
    float Runs;
    float Balls;
    float NotOuts;
};


// Constructors method which initializes class variables
playerNode::playerNode()
{
    FirstName = "unknown";
    LastName = "unknown";
    Matches = 0;
    Runs = 0;
    Balls = 0;
    NotOuts = 0;
    next = NULL;
    prev = NULL;


}

playerNode::playerNode(string newFirstName, string newLastName, float newMatches, float newRuns, float newBalls, float newNotOuts)
{
    FirstName = newFirstName;
    LastName = newLastName;
    Matches = newMatches;
    Runs = newRuns;
    Balls = newBalls;
    NotOuts = newNotOuts;
}


// Returns the playerNode's first name 
string playerNode::getFirstName()
{
    return FirstName;
}

// Returns the playerNode's last name 
string playerNode::getLastName()
{
    return LastName;
}

// Returns the playerNode's matches
float playerNode::getMatches()
{
    return Matches;
}

// Returns the playerNode's runs
float playerNode::getRuns()
{
    return Runs;
}

// Returns the playerNode's balls
float playerNode::getBalls()
{
    return Balls;
}

// Returns the playerNode's not outs
float playerNode::getNotOuts()
{
    return NotOuts;
}

// Sets the first name of the playerNode
void playerNode::setFirstName(string newFirstName)
{
    FirstName = newFirstName;
}

// Sets the last name of the playerNode
void playerNode::setLastName(string newLastName)
{
    LastName = newLastName;

}

// Sets the matches of the playerNode
void playerNode::setMatches(float newMatches)
{
    Matches = newMatches;
}

// Sets the runs of the playerNode
void playerNode::setRuns(float newRuns)
{
    Runs = newRuns;
}

// Sets the balls of the playerNode
void playerNode::setBalls(float newBalls)
{
    Balls = newBalls;
}

// Sets the not outs of the playerNode
void playerNode::setNotOuts(float newNotOuts)
{
    NotOuts = newNotOuts;
}

// The following member function calculates the dismissals of the playerNode
float playerNode::calcDismissals()
{

    return (Matches - NotOuts);
}

// The following member function calculates the batting average of the playerNode
float playerNode::calcBattingAverage()
{
    return (Runs/calcDismissals());
}

// The following member function calculates the batting strike rate of the playerNode
float playerNode::calcBattingStrikeRate()
{
    return (Runs/Balls)*100;
}

void playerNode::printplayerNodes()
{
    cout << "First Name: " << getFirstName()<< endl;
    cout << "Last Name: " << getLastName()<< endl;
    cout << "Matches: " << getMatches() << endl;
    cout << "Runs: " << getRuns() << endl;
    cout << "Balls: " << getBalls() << endl;
    cout << "NotOuts: " << getNotOuts() << endl;
}

