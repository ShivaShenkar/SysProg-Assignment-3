#pragma once
#include "Game.hpp"
#include "Game.hpp"
#include <string>
#include <stdexcept>
#include <iostream>
using std::string;
using std::cout;
using std::endl;
namespace coup
{
    class Player
    {
    protected:  
        Game game;
        int playerCoins;
        virtual void checkBeforeAction(string action,int price, Player *target =nullptr);
        void doAfterAction(bool lastActionWasTax=false,string nameArrested="");
    public:
        string type;
        string name,lastArrested;
        bool isSanctioned,isAbleToArrest,isCoupImmune,lastActionWasTax,bribeFlag;  
        Player(Game &game, string name);

        //mandatory methods from guide + methods from demo.cpp
        int coins() const;
        void gather();
        virtual void tax();
        void bribe();
        void arrest(Player &target);
        void sanction(Player &target);
        void coup(Player &target);
        virtual void undo(Player &target);

        
        void removeCoins(int amount);
        void addCoins(int amount); 
        //rule of three
        Player(const Player &other);
        Player &operator=(const Player &other);
        ~Player();
    };
}