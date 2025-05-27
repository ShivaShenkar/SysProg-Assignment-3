
#include "../include/General.hpp"
namespace coup
{
    General::General(Game &game, string name) : Player(game, name) {
        type = "General";
    }
    void General::coup_immune(Player &target) {
        checkBeforeAction("coup_immune", 5);
        removeCoins(5);
        target.isCoupImmune=true;
        doAfterAction();
    }
}