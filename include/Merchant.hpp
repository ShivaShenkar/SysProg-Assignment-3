#pragma once
#include "Player.hpp"
namespace coup{
    class Merchant : public Player {    
    protected:
        void checkBeforeAction(std::string action, int price, Player *target = nullptr) override;
    public:
        Merchant(Game &game, const std::string &name);
        
    };
}