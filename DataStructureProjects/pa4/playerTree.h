#include <string>
#include <fstream>
#include <iomanip>
#include "playerNode.h"
#define MAX_CAPACITY 20


// Definition of playerBT class
class playerBT {
private:
    // Stores list of players with a max capacity of 20
    playerNode* players[MAX_CAPACITY];

    // Initialization of current Capacity variable which will be used to track the current capacity of players in list
    int count = 0;

    // BT Root node
    playerNode* root = nullptr;


public:
    // default constructor
    playerBT();
    
    // default destructor
    ~playerBT();

    // textFile Constructor
    playerBT(string inputfileName, string outputfileName);

    // List functions
    void addplayer(playerNode p);
    playerNode*& getNext();
    bool hasNext();
    void clear();
    bool isFull();
    int getcount();

    // Print functions
    void printToFile(string fileName);
    void printPlayers();

    // Calc Function for getting the highest batting average among players
    playerNode* getHighestBattingAvg();

    // Linked List Functions
    //void sortByLastName();

    //Binary Tree Functions
    //Private
    playerNode* insertSorter(playerNode* node, playerNode* newNode);
    playerNode* removeSorter(playerNode* node, string first, string last);

    //Public
    void remove(string first, string last);
    void insert(playerNode* node);

    // Method to get the count of nodes in the tree
    int getCount();

    // Method to print the nodes of the tree in sorted order
    void printtoFile(string fileName, playerNode* node);
    void printTree(playerNode* node);

    // Getter method for root node
    playerNode* getRoot();

    // Recursive helper function to count the number of nodes in the tree
    int countHelper(playerNode* node);

};

// Default constructor for playerBT
playerBT::playerBT()
{

}

playerBT::~playerBT()
{

}



// list position increment function
playerNode*& playerBT::getNext() {

    // Index variable to be compared each call to the current capacity of the list
    static int index = 0;

    // Returns the next playerNode in the list if the index value is less than the capacity
    if (index < count) {
        return players[index++];
    }

    // if the index is equal to the capacity, then the index is set to equal zero
    // function returns the playerNode at the final index
    index = 0;

    return players[index];
}

// returns an index value if the index is less than the current capacity meaning the index has not reached the end of the list
bool playerBT::hasNext() {
    static int index = 0;
    return index < count;
}

// clears the capacity of the list to 0
// all operations are based on the current capacity value, therefore if current capacity is set to 0
// list will be empty
void playerBT::clear() {
    count = 0;
}

// checks to see if count is equal to the max value of the list
bool playerBT::isFull() {
    return count == MAX_CAPACITY;
}

// get count of list
int playerBT::getcount() {
    return count;
}



// calculate the highest batting average
playerNode* playerBT::getHighestBattingAvg()
{
    // intiialize and declare dummy variables 
    playerNode* p = nullptr;
    playerNode* HighestBattingplayerNode = p;
    int HighestBattingAVG = 0;

    // Loop through list while i is not equal to the capacity of the list
    for (int i = 0; i < count; i++)
    {
        // Sets the HighestBattingAverage to the current playerNode in the list of their batting average is higher than the current highest batting average
        if (players[i]->calcBattingAverage() > HighestBattingAVG)
        {
            HighestBattingAVG = players[i]->calcBattingAverage();
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
void playerBT::printToFile(string fileName)
{
    // Initialize ofstream filename
    ofstream file(fileName);

    // Check to see if file opens 
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }
    // returns the highest batting avg playerNode to get playerNode information for printing
    playerNode* p = getHighestBattingAvg();
    file << "playerNode Report --- " << count << " Players found in the input file" << endl;
    file << "Highest Batting Average -\t" << p->getLastName() << ", " << p->getFirstName() << endl << endl;
    file << "playerNode NAME" << right << " \t\tDismissals\t\tBatting_Strike_Rate\t\tBatting_Average " << endl;
    file << "-------------------------------------------------------------------------------------------------" << endl;

    // Loops through list and displays playerNode information
    for (int i = 0; i < count; i++)
    {
        file << players[i]->getFirstName() << " " << players[i]->getLastName() << right << " \t\t\t" << players[i]->calcDismissals() << "\t\t\t" << players[i]->calcBattingStrikeRate() << " \t\t\t\t" << players[i]->calcBattingAverage() << endl;

    }



}

// Constructor which generates a list from a file name and outputs to a file
playerBT::playerBT(string inputfileName, string outputfileName)
{

    // Messages to give feedback to the user that the constructor is running
    cout << "Reading players data from : " << inputfileName << endl;
    cout << "The result has been written to output file : " << outputfileName << endl;

    // Initialize playerBT object
    playerBT list;

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
        list.insert(&temp[playerCount]);

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

/*

New Binary Tree Method Additions below...

*/


// Method to insert a new node in the tree
void playerBT::insert(playerNode* node)
{
    if (count < MAX_CAPACITY)
    {
        playerNode* newNode = new playerNode(node->getFirstName(), node->getLastName(), node->getMatches(), node->getRuns(), node->getBalls(), node->getNotOuts());
        root = insertSorter(root, newNode);
        count++;  // Increment count
    }

}

playerNode* playerBT::insertSorter(playerNode* node, playerNode* newNode) {
    if (node == NULL) {
        return newNode;
    }
    if (newNode->getLastName() < node->getLastName()) {
        node->setLeft(insertSorter(node->getLeft(), newNode));
    }
    else if (newNode->getLastName() > node->getLastName()) {
        node->setRight(insertSorter(node->getRight(), newNode));
    }
    return node;
}



playerNode* playerBT::removeSorter(playerNode* node, string first, string last) 
{
    if (node == NULL) {
        return node;
    }
    if (last < node->getLastName()) {
        node->setLeft(removeSorter(node->getLeft(), first, last));
    }
    else if (last > node->getLastName()) {
        node->setRight(removeSorter(node->getRight(), first, last));
    }
    else if (first < node->getFirstName()) {
        node->setLeft(removeSorter(node->getLeft(), first, last));
    }
    else if (first > node->getFirstName()) {
        node->setRight(removeSorter(node->getRight(), first, last));
    }
    else {  // Node to be removed found
        if (node->getLeft() == NULL) {  // If node has no left child, replace with right child
            playerNode* temp = node->getRight();
            delete node;
            if (temp != NULL) {
                count--;
            }
            return temp;
        }
        else if (node->getRight() == NULL) {  // If node has no right child, replace with left child
            playerNode* temp = node->getLeft();
            delete node;
            if (temp != NULL) {
                count--;
            }
            return temp;
        }
        // If node has both left and right child, find the inorder successor (smallest node in the right subtree)
        playerNode* temp = node->getRight();
        while (temp->getLeft() != NULL) {
            temp = temp->getLeft();
        }
        // Copy the data from the inorder successor to the current node
        node->setFirstName(temp->getFirstName());
        node->setLastName(temp->getLastName());
        // Remove the inorder successor from the right subtree
        node->setRight(removeSorter(node->getRight(), temp->getFirstName(), temp->getLastName()));
        if (node->getRight() != NULL) {
            count--;
        }
    }
    return node;
}

// Method to remove a node from the tree
void playerBT::remove(string first, string last) {
    root = removeSorter(root, first, last);
    if (root != NULL) {  // If root is not null, decrement count
        count--;
    }
}


// Method to get the count of nodes in the tree
int playerBT::getCount() {
    return countHelper(root);
}



// Method to print the nodes of the tree in sorted order
void playerBT::printtoFile(string fileName, playerNode* node) {

        // Initialize ofstream filename
    ofstream file(fileName);

    // Check to see if file opens 
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        return;
    }
    // returns the highest batting avg playerNode to get playerNode information for printing
    playerNode* p = getHighestBattingAvg();
    file << "playerNode Report --- " << count << " Players found in the input file" << endl;
    file << "Highest Batting Average -\t" << p->getLastName() << ", " << p->getFirstName() << endl << endl;
    file << "playerNode NAME" << right << " \t\tDismissals\t\tBatting_Strike_Rate\t\tBatting_Average " << endl;
    file << "-------------------------------------------------------------------------------------------------" << endl;

    if (node == NULL) {
        return;
    }
    // Recursively print nodes in left subtree, current node, and right subtree
    printTree(node->getLeft());
    file << node->getFirstName() << " " << node->getLastName() << right << " \t\t\t" << node->calcDismissals() << "\t\t\t" << node->calcBattingStrikeRate() << " \t\t\t\t" << node->calcBattingAverage() << endl;
    printTree(node->getRight());

  

}


// Getter method for root node
playerNode* playerBT::getRoot() {
    return root;
}

// Recursive helper function to count the number of nodes in the tree
int playerBT::countHelper(playerNode* node) {
    if (node == NULL) {  // If current node is null, return 0
        return 0;
    }
    // Recursively count nodes in left and right subtrees and add 1 for the current node
    return 1 + countHelper(node->getLeft()) + countHelper(node->getRight());
}