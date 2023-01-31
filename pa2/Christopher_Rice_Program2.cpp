#include "playerList.h"

int main() {
    
    playerList list;

    list.addplayer(player("Chris","Rice",10,20,30,40));
    list.addplayer(player("Elizabeth","Rice",10,20,30,40));


    list.printPlayers();



    return 0;
}
