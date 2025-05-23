#include "Player.hpp"
#include "General.hpp"

General::General(Game &game, string name) : Player(game, name) {
    type = "General";
}
void General::coup_immune(Player &target) {
    removeCoins(5);
   target.setCoupImmune();
}