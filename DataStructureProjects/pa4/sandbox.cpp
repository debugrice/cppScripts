#include <iostream>
#include <string>
using namespace std;

// Definition of PlayerNode class
class PlayerNode {
private:
    string firstName;
    string lastName;
    PlayerNode* left;  // Pointer to left child
    PlayerNode* right;  // Pointer to right child
public:
    PlayerNode(string first, string last) {
        firstName = first;
        lastName = last;
        left = NULL;  // Initialize left child to null
        right = NULL;  // Initialize right child to null
    }

    // Setter methods for left and right child pointers
    void setLeft(PlayerNode* node) {
        left = node;
    }

    void setRight(PlayerNode* node) {
        right = node;
    }

    // Setter methods for first name and last name
    void setFirstName(string first) {
        firstName = first;
    }

    void setLastName(string last) {
        lastName = last;
    }

    // Getter methods for left and right child pointers
    PlayerNode* getLeft() {
        return left;
    }

    PlayerNode* getRight() {
        return right;
    }

    // Getter methods for first name and last name
    string getFirstName() {
        return firstName;
    }

    string getLastName() {
        return lastName;
    }
};

// Definition of PlayerTree class
class PlayerTree {
private:
    PlayerNode* root;  // Pointer to root node
    int count;  // Count of nodes in the tree
    
    PlayerNode* insertHelper(PlayerNode* node, PlayerNode* newNode) {
        if (node == NULL) {
            return newNode;
        }
        if (newNode->getLastName() < node->getLastName()) {
            node->setLeft(insertHelper(node->getLeft(), newNode));
        }
        else if (newNode->getLastName() > node->getLastName()) {
            node->setRight(insertHelper(node->getRight(), newNode));
        }
        return node;
    }



    PlayerNode* removeHelper(PlayerNode* node, string first, string last) {
        if (node == NULL) {
            return node;
        }
        if (last < node->getLastName()) {
            node->setLeft(removeHelper(node->getLeft(), first, last));
        }
        else if (last > node->getLastName()) {
            node->setRight(removeHelper(node->getRight(), first, last));
        }
        else if (first < node->getFirstName()) {
            node->setLeft(removeHelper(node->getLeft(), first, last));
        }
        else if (first > node->getFirstName()) {
            node->setRight(removeHelper(node->getRight(), first, last));
        }
        else {  // Node to be removed found
            if (node->getLeft() == NULL) {  // If node has no left child, replace with right child
                PlayerNode* temp = node->getRight();
                delete node;
                if (temp != NULL) {
                    count--;
                }
                return temp;
            }
            else if (node->getRight() == NULL) {  // If node has no right child, replace with left child
                PlayerNode* temp = node->getLeft();
                delete node;
                if (temp != NULL) {
                    count--;
                }
                return temp;
            }
            // If node has both left and right child, find the inorder successor (smallest node in the right subtree)
            PlayerNode* temp = node->getRight();
            while (temp->getLeft() != NULL) {
                temp = temp->getLeft();
            }
            // Copy the data from the inorder successor to the current node
            node->setFirstName(temp->getFirstName());
            node->setLastName(temp->getLastName());
            // Remove the inorder successor from the right subtree
            node->setRight(removeHelper(node->getRight(), temp->getFirstName(), temp->getLastName()));
            if (node->getRight() != NULL) {
                count--;
            }
        }
        return node;
    }



    // Recursive helper function to count the number of nodes in the tree
    int countHelper(PlayerNode* node) {
        if (node == NULL) {  // If current node is null, return 0
            return 0;
        }
        // Recursively count nodes in left and right subtrees and add 1 for the current node
        return 1 + countHelper(node->getLeft()) + countHelper(node->getRight());
    }

    // Recursive helper function to destroy the tree and free up memory
    void destroyTree(PlayerNode* node) {
        if (node != NULL) {
            // Recursively delete all nodes in the left and right subtrees
            destroyTree(node->getLeft());
            destroyTree(node->getRight());
            // Delete the current node
            delete node;
        }
    }

public:
    PlayerTree() {
        root = NULL;  // Initialize root to null
        count = 0;  // Initialize count to 0
    }

    // Destructor to free up memory
    ~PlayerTree() {
        destroyTree(root);
    }

    // Method to insert a new node in the tree
    void insert(string first, string last) {
        PlayerNode* newNode = new PlayerNode(first, last);
        root = insertHelper(root, newNode);
        count++;  // Increment count
    }

    // Method to remove a node from the tree
    void remove(string first, string last) {
        root = removeHelper(root, first, last);
        if (root != NULL) {  // If root is not null, decrement count
            count--;
        }
    }

    // Method to get the count of nodes in the tree
    int getCount() {
        return countHelper(root);
    }

    // Method to print the nodes of the tree in sorted order
    void printTree(PlayerNode* node) {
        if (node == NULL) {
            return;
        }
        // Recursively print nodes in left subtree, current node, and right subtree
        printTree(node->getLeft());
        cout << node->getLastName() << ", " << node->getFirstName() << endl;
        printTree(node->getRight());
    }

    // Getter method for root node
    PlayerNode* getRoot() {
        return root;
    }
};


int main() {
    PlayerTree tree;
    tree.insert("Chris", "Rice");
    tree.insert("Jane", "Doe");
    tree.insert("Bob", "Benton");
    tree.insert("Alice", "Smith");
    tree.printTree(tree.getRoot());  // Print all the nodes of the tree
    cout << "Count: " << tree.getCount() << endl;
    return 0;
}