#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <vector>
#include "Player.hpp"
using std::vector;
using namespace coup;


class PlayerController{
    private:
        Player& player;
        vector<Button> actionButtons;

        sf::Font font;

    public:
        PlayerController(Player& player,float x, float y, sf::Font& font);
        void draw(sf::RenderWindow& window) const;
        sf::Text playerCoinsText;
        sf::Text playerNameText;
        sf::Text playerRoleText;
        // Expose actionButtons for GUI event handling
        const std::vector<Button>& getActionButtons() const { return actionButtons; }
        Player& getPlayer() { return player; }
};