#include "Player.hpp"
#include "Game.hpp"
#include <string>
#include <stdexcept>
using std::string;
namespace coup{

    Player::Player(Game &game, string name) : game(game), name(name),playerCoins(0),isAbleToArrest(true),lastArrested(""),type("Player"),isCoupImmune(false),isSanctioned(false),lastActionWasTax(false),bribeFlag(false) {
        if(game.has_name(name)){
            throw std::invalid_argument("Player name already exists");
        }
        game.add_player(name);
    }


    void Player::gather() {
        checkBeforeAction("gather", 0);
        playerCoins += 1;
    }


    void Player::tax() {
        checkBeforeAction("tax", 0);
        playerCoins += 2;
        lastActionWasTax = true;
    }


    void Player::bribe() {
        checkBeforeAction("bribe", 4);
        if(bribeFlag) {
            throw std::runtime_error("You cannot bribe twice in a row");
        }
        playerCoins -= 4;
        bribeFlag = true;
        //checkBeforeAction
    }


    void Player::arrest(Player &target) {
        checkBeforeAction("arrest", 0, &target);
        if(lastArrested==target.name){
            throw std::runtime_error("You cannot arrest dtdfethe same player twice in a row");
        }
        if(target.type!="General"){
            if(target.type=="Merchant")
                target.playerCoins-=2;
            else{
                target.playerCoins-=1;
                playerCoins+=1;
            }
        }
    }


    void Player::sanction(Player &target) {
        if(target.type=="Judge"){
            checkBeforeAction("sanction", 4, &target);
            playerCoins-=1;
        }
        else
            checkBeforeAction("sanction", 3, &target);
        playerCoins -= 3;
        if(target.type=="Baron"){
            target.playerCoins+=1;
        }
        target.isSanctioned = true;
    }


    void Player::coup(Player &target) {
        checkBeforeAction("coup", 7, &target);
        target.playerCoins-=7;
        if(target.isCoupImmune) {
            target.isCoupImmune = false;
            // throw std::runtime_error("Target player is coup immune");
        }
        else
            game.remove_player(target.name);
    }


    void Player::undo(Player &target) {
        checkBeforeAction("undo", 0, &target);
        if(type=="Governor"){
            if(!target.lastActionWasTax)
                throw std::runtime_error("Governor cannot undo this action");
            target.playerCoins-=2;
            if(target.type=="Governor")
                target.playerCoins-=1;
        }
        if(type=="Judge"){
            if(!target.bribeFlag)
                throw std::runtime_error("No active bribe to undo");
            target.bribeFlag = false;
        }
        throw std::runtime_error(type+" don't have undo action");
        
    }


    void Player::checkBeforeAction(string action,int price, Player *target =nullptr) {
        if (!game.has_name(name))
            throw std::runtime_error("Player not found in the game");
        if(game.turn() != name) {
            throw std::runtime_error("It's not your turn");
            
        }
        if(target!=nullptr){
            if (!game.has_name(target->name))
                throw std::runtime_error("Target player not found in the game");
        } 
        if(playerCoins < price) {
            throw std::runtime_error("Not enough coins");
        }


        if ((action == "gather" ||action=="tax")&& isSanctioned) {
            throw std::runtime_error("You are sanctioned and cannot perform this action");
        }
        if(action=="arrest" && !isAbleToArrest) {
            throw std::runtime_error("Arrest function is disabled!");
        }
        if(playerCoins>=10 && action!="coup") {
            throw std::runtime_error("You have 10 or more coins, you must coup");

        }
        if(type=="Merchant")
        {
            if(playerCoins >=3)
                playerCoins++;
        }

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
    
    
    


    
    
    
}