#include "../include/Merchant.hpp"
namespace coup{
    Merchant::Merchant(Game &game, const std::string &name) : Player(game, name) {
        type = "Merchant";
    }
    void Merchant::doAfterAction(bool lastActionWasTax, std::string nameArrested) {
        if(playerCoins >=3)
                playerCoins++;
        Player::doAfterAction(lastActionWasTax, nameArrested);
    }
}