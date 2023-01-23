#include <iostream>
using namespace std;

class playerClass {
public:

    playerClass();
    
    string getFirstName();
    string getLastName();
    int getMatches();
    int getRuns();
    int getBalls();
    int getNotOuts();

    string setFirstName(string newFirstName);
    string setLastName(string newLastName);
    void setMatches(int newMatches);
    void setRuns(int newRuns);
    void setBalls(int newBalls);
    void setNotOuts(int newNotOuts);

    int calcDismissals();
    int calcBattingAverage();
    int calcBattingStrikeRate();

    
private:
    string FirstName;
    string LastName;
    int Matches;
    int Runs;
    int Balls;
    int NotOuts;
    int Playerarr[4] = {Matches, Runs, Balls, NotOuts};
};

playerClass::playerClass()
{
    FirstName = "unknown";
    LastName = "unknown";
    Matches = 0;
    Runs = 0;
    Balls = 0;
    NotOuts = 0;


}

string playerClass::getFirstName()
{
    return FirstName;
}

string playerClass::getLastName()
{
    return LastName;
}


int playerClass::getMatches()
{
    return Matches;
}

int playerClass::getRuns()
{
    return Runs;
}

int playerClass::getBalls()
{
    return Balls;
}

int playerClass::getNotOuts()
{
    return NotOuts;
}

string playerClass::setFirstName(string newFirstName)
{
    FirstName = newFirstName;
}

string playerClass::setLastName(string newLastName)
{
        LastName = newLastName;

}

void playerClass::setMatches(int newMatches)
{
    Matches = newMatches;
}

void playerClass::setRuns(int newRuns)
{
    Runs = newRuns;
}

void playerClass::setBalls(int newBalls)
{
    Balls = newBalls;
}

void playerClass::setNotOuts(int newNotOuts)
{
    NotOuts = newNotOuts;
}

int playerClass::calcDismissals()
{
    return (Matches - NotOuts);
}

int playerClass::calcBattingAverage()
{
    return (Runs/calcDismissals());
}

int playerClass::calcBattingStrikeRate()
{
    return (Runs/Balls)*100;
}


