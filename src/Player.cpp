#include "../include/Player.hpp"

namespace coup{

    Player::Player(Game &game, string name) : game(game), name(name),playerCoins(0),isAbleToArrest(true),lastArrested(""),type("Player"),isCoupImmune(false),isSanctioned(false),lastActionWasTax(false),bribeFlag(false) {
        if(game.has_name(name)){
            throw std::invalid_argument("Player name already exists");
        }
        game.add_player(name);
    }


    void Player::gather() {
        checkBeforeAction("gather", 0);
        addCoins(1);
        doAfterAction();
    }


    void Player::tax() {
        checkBeforeAction("tax", 0);
        addCoins(2);
        doAfterAction(true);
    }


    void Player::bribe() {
        checkBeforeAction("bribe", 4);
        if(bribeFlag) {
            throw std::runtime_error("You cannot bribe twice in a row");
        }
        bribeFlag = true;
    }


    void Player::arrest(Player &target) {
        checkBeforeAction("arrest", 0, &target);
        if(target.type!="General"){
            if(target.type=="Merchant"){
                switch (target.coins()) 
                {
                case 0: 
                    cout<< "The player " << target.name << " has no coins to pay for arrest." << endl;
                    break;
                case 1:
                    target.removeCoins(1);
                    addCoins(1);
                    break;
                
                default:
                    target.removeCoins(2);
                    break;
                }
            }
            else{
                if(target.coins()<1)
                    cout<< "The player " << target.name << " has no coins to pay for arrest." << endl;
                else{
                    target.removeCoins(1);
                    addCoins(1);
                }
            }
        }
        else{
            if(target.coins()==0)
                cout<< "The general " << target.name << " has no coins to pay for arrest." << endl;
            else
                cout<<"The general " << target.name << "was arrested but recieved his coin back" << endl;
        }
        doAfterAction(false, target.name);
    }


    void Player::sanction(Player &target) {
        if(target.type=="Judge"){
            checkBeforeAction("sanction", 4, &target);
        }
        else
            checkBeforeAction("sanction", 3, &target);
        if(target.type=="Baron"){
            target.addCoins(1);
        }
        target.isSanctioned = true;
        doAfterAction();
    }


    void Player::coup(Player &target) {
        checkBeforeAction("coup", 7, &target);
        if(target.isCoupImmune) {
            target.isCoupImmune = false;
            // throw std::runtime_error("Target player is coup immune");
        }
        else
            game.remove_player(target.name);
        doAfterAction();
    }


    void Player::undo(Player &target) {
        throw std::runtime_error(type+" don't have undo action");
        
    }


    void Player::checkBeforeAction(string action,int price, Player *target) {
        if (!game.has_name(name))
            throw std::runtime_error("Player not found in the game");
        
        if(action!="undo"){    
            if(game.turn() != name) {

                throw std::runtime_error("It's not your turn");
                
            }
        }
        if(target==nullptr){
            if (action == "arrest" || action == "sanction" || action == "coup" || action == "undo") {
                throw std::runtime_error("Target player is required for this action");
            }
        } else {
            if (!game.has_name(target->name)) {
                throw std::runtime_error("Target player not found in the game");
            }
        }
        
        if(playerCoins < price) {
            throw std::runtime_error("Not enough coins");
        }


        if ((action == "gather" ||action=="tax")&& isSanctioned) {
            throw std::runtime_error("You are sanctioned and cannot perform this action");
        }
        if(action=="arrest") {
            if(!isAbleToArrest)
                throw std::runtime_error("Arrest function is disabled!");
            if(lastArrested == target->name) {
                throw std::runtime_error("You cannot arrest the same player twice in a row");
            }
        }
        if(action!="watchCoins"&&action!="cancelArrest"&&action!="undo"){
            if(playerCoins>=10 && action!="coup") {
                throw std::runtime_error("You have 10 or more coins, you must coup");

            }
        }
        if(action!="invest")
            removeCoins(price);

    }

    void Player::doAfterAction(bool lastActionWasTax,string nameArrested) {
        if(bribeFlag) {
            bribeFlag = false;
        }
        else{
            game.next_turn();
            isSanctioned = false;
            isAbleToArrest = true;
            this->lastActionWasTax = lastActionWasTax;
            lastArrested = nameArrested;
        }
    }
    
    void Player::removeCoins(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Cannot remove a negative amount of coins");
        }
        playerCoins -= amount;
    }
    void Player::addCoins(int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Cannot add a negative amount of coins");
        }
        playerCoins += amount;
    }

    int Player:: coins() const{
        return playerCoins;
    }
    
    
    


    
    
    
}