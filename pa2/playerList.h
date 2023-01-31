#include <iostream>
#include <string>
#include "player.h"
#define MAX_SIZE 100


class playerList {
private:
    player players[MAX_SIZE];
    int size;

public:
    // default constructor
    playerList() : size(0) {}

    // add a player to the list
    void addplayer(player p) 
    {
        if (size < MAX_SIZE) 
            players[size++] = p;
    }

    // iterate through the list
    player& getNext() {
        static int index = 0;
        if (index < size) {
            return players[index++];
        }
        index = 0;
        return players[index];
    }

    bool hasNext() {
        static int index = 0;
        return index < size;
    }

    // clear the list
    void clear() {
        size = 0;
    }

    // check if list is full
    bool isFull() {
        return size == MAX_SIZE;
    }

    // get size of list
    int getSize() {
        return size;
    }
};

