//fikhman2005@gmail.com
#include "../../include/Button.hpp"

Button::Button(float x, float y, float width, float height, const string& buttonText, sf::Font& font, sf::Color bgColor, sf::Color textColor)
    : bgColor(bgColor), textColor(textColor) {
        shape.setSize(sf::Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(bgColor);
        text.setFont(font);
        text.setString(buttonText);
        text.setCharacterSize(18); // Slightly smaller for better fit
        text.setFillColor(textColor);
        // Center text in button
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + width / 2.0f, y + height / 2.0f);
    }
    void Button::draw(sf::RenderWindow& window) const {
        window.draw(shape);
        window.draw(text);
    }
    void Button::setPosition(float x, float y) {
        shape.setPosition(x, y);
        // Center text in button
        sf::Vector2f size = shape.getSize();
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        text.setPosition(x + size.x / 2.0f, y + size.y / 2.0f);
    }
    sf::FloatRect Button::getGlobalBounds() const {
        return shape.getGlobalBounds();
    }
    std::string Button::getLabel() const {
        return text.getString();
    }

