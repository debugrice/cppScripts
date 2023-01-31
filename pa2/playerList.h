#include <iostream>
#include <string>
#include "player.h"
#define MAX_CAPACITY 100


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

};

playerList::playerList()
{

}

// add a player to the list
void playerList::addplayer(player p) 
{
    // if the Current Capacity is less than the max capacity of the list then add a player to the next element in the list
    if (currentCapacity < MAX_CAPACITY) 
        // set current element to the 
        cout << "Current Capacity: " << currentCapacity << endl;
        players[currentCapacity++] = p;
}  

// list position increment function
player& playerList::getNext() {

    // Index variable to be compared each call to the current capacity of the list
    // 
    static int index = 0;
    
    // Returns the next player in the list if the index value is 
    if (index < currentCapacity) {
        return players[index++];
    }

    index = 0;
    
    return players[index];
}

bool playerList::hasNext() {
    static int index = 0;
    return index < currentCapacity;
}

// clear the list
void playerList::clear() {
    currentCapacity = 0;
}

// check if list is full
bool playerList::isFull() {
    return currentCapacity == MAX_CAPACITY;
}

// get currentCapacity of list
int playerList::getcurrentCapacity() {
    return currentCapacity;
}