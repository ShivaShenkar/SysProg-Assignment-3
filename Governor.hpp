#include "Player.hpp"

class Governor : public Player
{
public:
    Governor(Game &game, const string &name) : Player(game, name) {}

    void tax();
    void undo();

};