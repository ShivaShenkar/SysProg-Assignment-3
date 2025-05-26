#include "Baron.hpp"
namespace coup{
    Baron::Baron(Game &game, string name) : Player(game, name){
        type = "Baron";
    }
    void Baron::invest() {
        addCoins(3);
    }
}