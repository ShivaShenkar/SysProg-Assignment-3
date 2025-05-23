#include "Player.hpp"
class Spy : public Player
{
public:
    Spy(Game &game, const string &name) : Player(game, name) {}
    int watchCoins(Player &target);
    void cancelArrest(Player &target);
    
};