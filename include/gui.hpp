#pragma once
#include "PlayerEntry.hpp"
#include "PlayerController.hpp"
#include <iostream>
#include <memory>
#include "Baron.hpp"
#include "General.hpp"
#include "Governor.hpp"
#include "Judge.hpp"
#include "Merchant.hpp"
#include "Spy.hpp"



class GUI{
    private:
        sf::RenderWindow window;
        sf::Font mainFont;
        sf::Font titleFont;
        void gameSettings();
        void gamePage(vector<PlayerEntry>& playerEntries);
        void actionInterface(string actionName, Player& player, std::vector<std::unique_ptr<Player>>& players);
    public:
        GUI();
        void startGame();
        
};
void organizeList(std::vector<PlayerEntry>& playerEntries);


