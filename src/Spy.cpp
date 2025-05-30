//fikhman2005@gmail.com
#include "../include/Spy.hpp"
namespace coup{
    Spy::Spy(Game &game, const string &name) : Player(game, name) {
        type = "Spy";
    }
    int Spy::watchCoins(Player &target) {
        checkBeforeAction("watchCoins", 0, &target);
        return target.coins();
    }
    void Spy::cancelArrest(Player &target) {
        checkBeforeAction("cancelArrest", 0, &target);
        target.isAbleToArrest = false;
    }
}