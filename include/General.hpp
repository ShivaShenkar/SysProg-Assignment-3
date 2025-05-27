#pragma once
#include "Player.hpp"
namespace coup{
    class General:public Player{
        public:
            General(Game &game, string name);
            void coup_immune(Player &target);
    };
}