//fikhman2005@gmail.com
#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Button.hpp"

class PopupWindow {
private:
    std::string title;
    std::string message;
    sf::RenderWindow popupWindow;
    Button closeButton;
    sf::Text messageText;
    const sf::Font& font;
public:
    PopupWindow(const std::string& title, const std::string& message, sf::Font& font, int width = 400, int height = 180);
    void draw();
};
