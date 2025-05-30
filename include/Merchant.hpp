//fikhman2005@gmail.com
#pragma once
#include "Player.hpp"
namespace coup{
    class Merchant : public Player {    
    protected:
        void doAfterAction(bool lastActionWasTax=false, std::string nameArrested="") override;
    public:
        Merchant(Game &game, const std::string &name);
        
    };
}