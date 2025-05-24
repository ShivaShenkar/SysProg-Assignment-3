#pragma once
#include "Game.hpp"
namespace coup
{
    class Player
    {
    protected:  
        Game game;
        int playerCoins;
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
        void undo(Player &target);

        void checkBeforeAction(string action,int price, Player *target =nullptr);
        void doAfterAction();
        //rule of three
        Player(const Player &other);
        Player &operator=(const Player &other);
        ~Player();
    };
}