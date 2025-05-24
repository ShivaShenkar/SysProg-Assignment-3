#include "Player.hpp"
#include "Governor.hpp"
using std::string;
#include <stdexcept>
namespace coup {
    Governor::Governor(Game &game, const string &name) : Player(game, name) {
        type = "Governor";
    }
    void Governor::tax() {
        Player::tax();
        playerCoins+=1;
    }
}