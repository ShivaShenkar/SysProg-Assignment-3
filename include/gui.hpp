//fikhman2005@gmail.com
#pragma once
#include "PopupWindow.hpp"
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
        Player* actionInterface(string actionName, Player& player, std::vector<std::unique_ptr<Player>>& players, Game& game);
        void victoryPage(const std::string& winner);
    public:
        GUI();
        void startGame();
        
    };
void organizeList(std::vector<PlayerEntry>& playerEntries);


