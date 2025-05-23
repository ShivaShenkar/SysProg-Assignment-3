#include "Spy.hpp"
#include <string>
using std::string;

Spy::Spy(Game &game, const string &name) : Player(game, name) {
    type = "Spy";
}
int Spy::watchCoins(Player &target) {
    return target.coins();
}
void Spy::cancelArrest(Player &target) {
    target.setCanceledArrest();
}