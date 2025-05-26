
#include "Spy.hpp"
namespace coup{
    Spy::Spy(Game &game, const string &name) : Player(game, name) {
        type = "Spy";
    }
    int Spy::watchCoins(Player &target) {
        return target.coins();
    }
    void Spy::cancelArrest(Player &target) {
        target.isAbleToArrest = false;
    }
}