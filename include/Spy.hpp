//fikhman2005@gmail.com
#pragma once
#include "Player.hpp"
namespace coup{
    class Spy : public Player
    {
    public:
        Spy(Game &game, const string &name);
        int watchCoins(Player &target);
        void cancelArrest(Player &target);
        
    };
}