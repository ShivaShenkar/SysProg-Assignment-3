#include "Player.hpp"
#include "Governor.hpp"
using std::string;
#include <stdexcept>

Governor::Governor(Game &game, const string &name) : Player(game, name) {}
void Governor::tax() {
    if (game.turn() != getName()) {
        throw std::runtime_error("Not your turn");
    }
    addCoins(2);
}
void Governor::undo(Player &target) {
    if(game.turn() != getName()) {
        throw std::runtime_error("Not your turn");
    }
    if(!game.has_name(target.getName())){
        throw std::invalid_argument("Target player does not exist");
    }
    target.removeCoins(2);
}