#include <iostream>
#include <string>

const int MAX_SIZE = 20;

class Player {
public:
    std::string name;
    int score;

    // constructor
    Player(std::string n, int s) : name(n), score(s) {}
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
