#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"



class PlayerEntry {
    public:
        sf::Text nameText;
        sf::Text roleText;
        Button deleteButton;

        PlayerEntry(string name,string role,sf::Font& font, float y);
        void setPosition(float y);
        void draw(sf::RenderWindow& window) const;
};