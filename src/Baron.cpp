//fikhman2005@gmail.com
#include "../include/Baron.hpp"
namespace coup{
    Baron::Baron(Game &game, string name) : Player(game, name){
        type = "Baron";
    }
    void Baron::invest() {
        checkBeforeAction("invest", 3);
        addCoins(3);
        doAfterAction();

    }
}