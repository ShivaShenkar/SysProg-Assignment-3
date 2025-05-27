#include "../include/Merchant.hpp"
namespace coup{
    Merchant::Merchant(Game &game, const std::string &name) : Player(game, name) {
        type = "Merchant";
    }
    void Merchant::checkBeforeAction(std::string action, int price, Player *target) {
        if(playerCoins >=3)
                playerCoins++;
        Player::checkBeforeAction(action, price, target);
    }
}