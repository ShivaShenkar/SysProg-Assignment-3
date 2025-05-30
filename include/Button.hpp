//fikhman2005@gmail.com
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using std::string;

class Button {
    private:
        sf::Color bgColor;
        sf::Color textColor;
        sf::RectangleShape shape;
        sf::Text text;

    public:
        sf::FloatRect getGlobalBounds() const;
        Button(float x, float y, float width, float height, const string& buttonText, sf::Font& font,sf::Color bgColor = sf::Color::Blue, sf::Color textColor = sf::Color::White);
        void setPosition(float x, float y);
        void draw(sf::RenderWindow& window) const;
        std::string getLabel() const ;
};