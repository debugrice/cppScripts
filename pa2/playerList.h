class PlayerList {
private:
    Player players[MAX_SIZE];
    int size;

public:
    // default constructor
    PlayerList() : size(0) {}

    // add a player to the list
    void addPlayer(Player p) {
        if (size < MAX_SIZE) {
            players[size++] = p;
        }
    }

    // iterate through the list
    Player& getNext() {
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

int main() {
    PlayerList list;
    list.addPlayer(Player("Alice", 100));
    list.addPlayer(Player("Bob", 90));
    list.addPlayer(Player("Charlie", 80));

    while (list.hasNext()) {
        Player p = list.getNext();
        std::cout << p.name << " " << p.score << std::endl;
    }

    return 0;
}