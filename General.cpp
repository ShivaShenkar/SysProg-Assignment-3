using namespace coup;
#include "Player.hpp"
#include "General.hpp"
namespace coup
{
    General::General(Game &game, string name) : Player(game, name) {
        type = "General";
    }
    void General::coup_immune(Player &target) {
        playerCoins-=5;
        target.isCoupImmune=true;
    }
}