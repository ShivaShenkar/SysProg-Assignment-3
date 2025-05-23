#include "Baron.hpp"
#include "Player.hpp"
#include <string>
#include <stdexcept>
using std::string;

Baron::Baron(Game &game, string name) : Player(game, name){
    type = "Baron";
}
void Baron::invest() {
    addCoins(3);
}