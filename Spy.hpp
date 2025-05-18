#include "Player.hpp"
class Spy : public Player
{
public:
    Spy(Game &game, const string &name) : Player(game, name) {}
    void watchCoins(Player &target);
};