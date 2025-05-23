#pragma once
#include "Player.hpp"
#include <string>

class Governor : public Player
{
public:
    Governor(Game &game, const string &name);

    void tax() override;
    void undo(Player &target);

};