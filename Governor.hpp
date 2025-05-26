#pragma once
#include "Player.hpp"
#include <string>
using std::string;
#include <stdexcept>
namespace coup{
    class Governor : public Player
    {
    public:
        Governor(Game &game, const string &name);
        void tax() override;
        void undo(Player &target) override;
    };
}