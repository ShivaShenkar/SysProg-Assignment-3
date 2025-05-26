#include "Governor.hpp"
namespace coup {
    Governor::Governor(Game &game, const string &name) : Player(game, name) {
        type = "Governor";
    }
    void Governor::tax() {
        Player::tax();
        playerCoins+=1;
    }
    void Governor::undo(Player &target) {
        checkBeforeAction("undo", 0, &target);
        if(!target.lastActionWasTax)
            throw std::runtime_error("Governor cannot undo this action");
        target.removeCoins(2);
        if(target.type=="Governor")
            target.removeCoins(1);
    }
}