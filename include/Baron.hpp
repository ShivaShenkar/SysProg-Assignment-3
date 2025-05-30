//fikhman2005@gmail.com
#pragma once
#include <string>
#include "Player.hpp"
#include "Game.hpp"
using std::string;

namespace coup {
    class Baron : public Player {
        public:
            Baron(Game &game, string name);
            void invest();
    };
}