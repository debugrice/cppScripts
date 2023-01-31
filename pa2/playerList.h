#include <iostream>
#include <string>
#include "player.h"
#define MAX_CAPACITY 20


class playerList {
private:
    player players[MAX_CAPACITY];
    int currentCapacity = 0;

public:
    // default constructor
    playerList();
    
    // List functions
    void addplayer(player p);
    player& getNext();
    bool hasNext();
    void clear();
    bool isFull();
    int getcurrentCapacity();

    void printPlayers();

};

playerList::playerList()
{

}

// add a player to the list
void playerList::addplayer(player p) 
{
    // if the Current Capacity is less than the max capacity of the list then add a player to the next element in the list
    if (currentCapacity < MAX_CAPACITY) 
        // set current element in player list to player passed into function
        players[currentCapacity++] = p;
}  

// list position increment function
player& playerList::getNext() {

    // Index variable to be compared each call to the current capacity of the list
    static int index = 0;
    
    // Returns the next player in the list if the index value is less than the capacity
    if (index < currentCapacity) {
        return players[index++];
    }

    // if the index is equal to the capacity, then the index is set to equal zero
    // function returns the player at the final index
    index = 0;
    
    return players[index];
}

// returns an index value if the index is less than the current capacity meaning the index has not reached the end of the list
bool playerList::hasNext() {
    static int index = 0;
    return index < currentCapacity;
}

// clears the capacity of the list to 0
// all operations are based on the current capacity value, therefore if current capacity is set to 0
// list will be empty
void playerList::clear() {
    currentCapacity = 0;
}

// checks to see if currentCapacity is equal to the max value of the list
bool playerList::isFull() {
    return currentCapacity == MAX_CAPACITY;
}

// get currentCapacity of list
int playerList::getcurrentCapacity() {
    return currentCapacity;
}

// Given a player P, the following prints their information
void playerList::printPlayers()
{

    for (int i = 0; i < getcurrentCapacity(); i++)
    {
        // Need to find a way to add index
        cout << "First Name: " << players[i].getFirstName()<< endl;
        cout << "Last Name: " << players[i].getLastName()<< endl;
        cout << "Matches: " << players[i].getMatches() << endl;
        cout << "Runs: " << players[i].getRuns() << endl;
        cout << "Balls: " << players[i].getBalls() << endl;
        cout << "NotOuts: " << players[i].getNotOuts() << endl;
    }

}