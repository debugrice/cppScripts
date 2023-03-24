#include <string>
#include <fstream>
#include <iomanip>
#include "playerNode.h"
#define MAX_CAPACITY 20


// Definition of Playerlist class
class playerList {
private:
    // Stores list of players with a max capacity of 20
    playerNode players[MAX_CAPACITY];

    // Initialization of current Capacity variable which will be used to track the current capacity of players in list
    int currentCapacity = 0;

public:
    // default constructor
    playerList();

    // textFile Constructor
    playerList(string inputfileName, string outputfileName);
    
    // List functions
    void addplayer(playerNode p);
    playerNode& getNext();
    bool hasNext();
    void clear();
    bool isFull();
    int getcurrentCapacity();

    // Print functions
    void printToFile(string fileName);
    void printPlayers();

    // Calc Function for getting the highest batting average among players
    playerNode getHighestBattingAvg();

    // Linked List Functions
    void remove(string first, string last);
    void sortByLastName();

    // Head and Tail node initialization
    playerNode* head = NULL;
    playerNode* tail = NULL;
 


};

// Default constructor for playerlist
playerList::playerList()
{

}

// Constructor which generates a list from a file name and outputs to a file
playerList::playerList(string inputfileName, string outputfileName)
{

    // Messages to give feedback to the user that the constructor is running
    cout << "Reading players data from : " << inputfileName << endl;
    cout << "The result has been written to output file : " << outputfileName << endl;

    // Initialize playerlist object
    playerList list;

    // Initialize a dummy playerNode variable to access playerNode member functions
    playerNode* p = nullptr;


    // Variables to keep track of the number of players
    int playerCount = 0;

    // Open the file
    ifstream file(inputfileName);

    // Read each line of the file
    string line;
    while (getline(file, line)) {
        // Declare and nitialize dummy variables to be manipulated and then used to set actual object variables
        int i = 0;
        int field = 0;
        string firstName, lastName;
        int runs = 0;
        int notOuts = 0;
        int balls = 0;
        int matches = 0;
        int hits = 0;

        // Split the line into fields
        // The following loops until the variable i is equal to the end of the length of the line to ensure all characters are scanned
        while (i < line.length()) {

            // Initialize j to equal i
            int j = i;


            // The following loop scans until the variable j is no longer less than the length of the line, and a space is not encountered.
            // When is a space is encountered or the end of the line is reached, the while loop breaks
            while (j < line.length() && line[j] != ' ') {
                j++;
            }

            // Field text equals the substring from i to j - 1 (minus one because the last j contains the space)
            string fieldText = line.substr(i, j - i);

            // Store the values in the appropriate variables via switch
            // the field value increments each time loop of i starting from 0 and therefore as long as the cases
            // are in order we can set the correct class variables to match.
            switch (field) {
            case 0:
                lastName = fieldText;
                break;
            case 1:
                firstName = fieldText;
                break;
            case 2:
                matches = stoi(fieldText);
                break;
            case 3:
                runs = stoi(fieldText);
                break;
            case 4:
                balls = stoi(fieldText);
                break;
            case 5:
                notOuts = stoi(fieldText);
                break;
            }

            // Increment each counter per loop
            field++;
            i = j + 1;
        }


        // Dynamically allocate a new array of playerNode objects
        playerNode* temp = new playerNode[playerCount + 1];
        for (int k = 0; k < playerCount; k++) {
            temp[k] = p[k]; // initialize each element in the temp array to equal the dummy playerNode array
        }


        // The temp array of players is used to access the member functions to set the private variables of each player
        temp[playerCount].setFirstName(firstName);
        temp[playerCount].setLastName(lastName);
        temp[playerCount].setMatches(matches);
        temp[playerCount].setRuns(runs);
        temp[playerCount].setBalls(balls);
        temp[playerCount].setNotOuts(notOuts);


        // Add the playerNode to the list each loop
        list.addplayer(temp[playerCount]);

        // Update the players pointer to point to the new array
        delete[] p;
        p = temp;

        playerCount++; // Increment the playerNode count
    }

    // Close the file
    file.close();

    // Print the players and their statistics
    list.printToFile(outputfileName);

    // Deallocate the memory used by the players array
    delete[] p;
}

// add a playerNode to the list
void playerList::addplayer(playerNode p) 
{
    // if the Current Capacity is less than the max capacity of the list then add a playerNode to the next element in the list
    if (currentCapacity < MAX_CAPACITY) 
        // set current element in playerNode list to playerNode passed into function
        players[currentCapacity++] = p;
}  

// list position increment function
playerNode& playerList::getNext() {

    // Index variable to be compared each call to the current capacity of the list
    static int index = 0;
    
    // Returns the next playerNode in the list if the index value is less than the capacity
    if (index < currentCapacity) {
        return players[index++];
    }

    // if the index is equal to the capacity, then the index is set to equal zero
    // function returns the playerNode at the final index
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

// print players to console
void playerList::printPlayers()
{
    playerNode* currNode = head;
    while (currNode != nullptr) {
        cout << currNode->getFirstName() << " " << currNode->getLastName() << endl;
        currNode = currNode->next;
    }

}

// calculate the highest batting average
playerNode playerList::getHighestBattingAvg()
{
    // intiialize and declare dummy variables 
    playerNode p;
    playerNode& HighestBattingplayerNode =  p;
    int HighestBattingAVG = 0;

    // Loop through list while i is not equal to the capacity of the list
    for (int i = 0; i < currentCapacity; i++)
    {
        // Sets the HighestBattingAverage to the current playerNode in the list of their batting average is higher than the current highest batting average
        if (players[i].calcBattingAverage() > HighestBattingAVG)
        {
            HighestBattingAVG = players[i].calcBattingAverage();
            HighestBattingplayerNode = players[i];
        }
        else
        {
            // do nothing
        }

    }

    return HighestBattingplayerNode;
}

// This function prints playerNode data to a text file given a filename
void playerList::printToFile(string fileName)
{
    // Initialize ofstream filename
    ofstream file(fileName);

    // Check to see if file opens 
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }
    // returns the highest batting avg playerNode to get playerNode information for printing
    playerNode p = getHighestBattingAvg();
    file << "playerNode Report --- " << currentCapacity << " Players found in the input file" << endl;
    file << "Highest Batting Average -\t" << p.getLastName() << ", " << p.getFirstName() << endl << endl;
    file << "playerNode NAME" << right << " \t\tDismissals\t\tBatting_Strike_Rate\t\tBatting_Average " << endl;
    file << "-------------------------------------------------------------------------------------------------" << endl;

    // Loops through list and displays playerNode information
    for (int i = 0; i < currentCapacity; i++)
    {
        //file << players[i].getFirstName() <<" " << players[i].getLastName() << "\t\t:\t\t" << players[i].calcDismissals() << "\t\t" << players[i].calcBattingStrikeRate() << " \t\t" << players[i].calcBattingAverage() << endl;
        file << players[i].getFirstName() << " " << players[i].getLastName() << right << " \t\t\t" << players[i].calcDismissals() << "\t\t\t" << players[i].calcBattingStrikeRate() << " \t\t\t\t" << players[i].calcBattingAverage() << endl;

    }



}

// Linked List Functions
void playerList::remove(string first, string last)
{
    playerNode* currNode = head;
    while (currNode != nullptr) {
        if (currNode->getFirstName() == first && currNode->getLastName() == last) {
            if (currNode == head) {
                head = currNode->next;
            }
            else {
                currNode->prev->next = currNode->next;
            }
            if (currNode == tail) {
                tail = currNode->prev;
            }
            else {
                currNode->next->prev = currNode->prev;
            }
            delete currNode;
            break;
        }
        currNode = currNode->next;
    }
}


void playerList::sortByLastName()
{
    if (head == nullptr || head == tail) {
        return;
    }
    bool swapped;
    playerNode* currNode;
    playerNode* lastNode = nullptr;
    do {
        swapped = false;
        currNode = head;
        while (currNode->next != lastNode) 
        {
            if (currNode->getLastName() > currNode->next->getLastName()) 
            {
                string tempFirst = currNode->getFirstName();
                string tempLast = currNode->getLastName();
                currNode->setFirstName(currNode->next->getFirstName());
                currNode->setLastName(currNode->next->getLastName());
                currNode->next->setFirstName(tempFirst);
                currNode->next->setLastName(tempLast);
                swapped = true;
            }
            currNode = currNode->next;
        }
        lastNode = currNode;
    } while (swapped);
}