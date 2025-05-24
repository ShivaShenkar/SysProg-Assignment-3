#pragma once
#include "Player.hpp"
#include <string>
namespace coup{
    class Governor : public Player
    {
    public:
        Governor(Game &game, const string &name);
        void tax() override;
    };
}