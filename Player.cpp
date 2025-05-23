#include "Player.hpp"
#include "Game.hpp"
#include <string>
#include <stdexcept>
using std::string;
Player::Player(Game &game, string name) : game(game), name(name),playerCoins(0),arrestFunctionFlag(false),lastArrested(""),type("Player"),coupImmune(false),isSanctioned(false) {
    if(game.has_name(name)){
        throw std::invalid_argument("Player name already exists");
    }
    game.add_player(name);
}
Player &Player::operator=(const Player &other) {
    if (this != &other) {
        game = other.game;
        name = other.name;
        playerCoins = other.playerCoins;
    }
    return *this;
}
int Player:: coins() const{
    return playerCoins;
}
void Player::gather() {
    if(isSanctioned) {
        throw std::runtime_error("You are sanctioned and cannot gather coins");
    }
    addCoins(1);
}
void Player::tax() {
    if(isSanctioned) {
        throw std::runtime_error("You are sanctioned and cannot tax");
    }
    addCoins(2);
}
void Player::bribe() {
    removeCoins(3);
    game.setCurrentTurn(name);
}
 void Player::setSanctioned(){
    isSanctioned = true;

}
void Player::sanction(Player &target) {
    if(target.getType()=="Baron"){
        target.addCoins(1);
    }
    target.setSanctioned();
}
void Player::addCoins(int coins) {
    if(coins < 0){
        throw std::invalid_argument("Coins cannot be negative");
    }
    playerCoins += coins;
}
void Player::removeCoins(int coins) {
    if(coins < 0){
        throw std::invalid_argument("Coins cannot be negative");
    }
    playerCoins -= coins;
}
string Player::getName() const {
    return name;
}
void Player::setCanceledArrest() {
    arrestFunctionFlag = true;
}
void Player::arrest(Player &target) {
    if(arrestFunctionFlag) {
        throw std::runtime_error("Arrest function is disabled!");
    }
    if(lastArrested==target.getName()){
        throw std::runtime_error("You cannot arrest the same player twice in a row");
    }
    if(target.getType()!="General"){
        target.removeCoins(1);
    }
    addCoins(1);

}
void Player::coup(Player &target) {
    target.removeCoins(7);
    game.remove_player(target.getName());
}
string Player::getType() const {
    return type;
}
void Player::setCoupImmune(){
    coupImmune = true;
}
void Player::undo(Player &target) {
    
    if(game.turn() != getName()) {
        throw std::runtime_error("Not your turn");
    }
    if(!game.has_name(target.getName())){
        throw std::invalid_argument("Target player does not exist");
    }
    if(target.getType()=="Governor"){
        
        target.removeCoins(2);
        addCoins(2);
    }
    if(target.getType()=="Judge"){
        
    }
    throw std::runtime_error(getType()+" don't have undo action");
    
}