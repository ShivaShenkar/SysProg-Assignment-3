//fikhman2005@gmail.com
#pragma once
#include "Player.hpp"
#include <stdexcept>
namespace coup {
    class Judge : public Player {
        public:
            Judge(Game &game, string name);
            void undo(Player &target) override;
    };
}