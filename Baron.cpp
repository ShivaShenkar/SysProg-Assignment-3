#include "Baron.hpp"
#include "Player.hpp"
#include <string>
#include <stdexcept>
using std::string;
namespace coup{
    Baron::Baron(Game &game, string name) : Player(game, name){
        type = "Baron";
    }
    void coup::Baron::invest() {
        playerCoins += 3;
    }
}