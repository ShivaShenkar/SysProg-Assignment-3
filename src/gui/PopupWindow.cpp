//fikhman2005@gmail.com
#include "../../include/PopupWindow.hpp"

PopupWindow::PopupWindow(const std::string& title, const std::string& message, sf::Font& font, int width, int height)
    : title(title), message(message), font(font),
      popupWindow(sf::VideoMode(width, height), title),
      closeButton(width/2 - 40, height - 50, 80, 35, "Close", font, sf::Color::Red)
{
    popupWindow.setFramerateLimit(60);
    popupWindow.setPosition(sf::Vector2i(200, 200));
    messageText.setFont(font);
    messageText.setString(message);
    messageText.setCharacterSize(20);
    messageText.setFillColor(sf::Color::Black);
    // Center message text
    sf::FloatRect textRect = messageText.getLocalBounds();
    messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    messageText.setPosition(width / 2.0f, height / 2.5f);
}

void PopupWindow::draw() {
    while (popupWindow.isOpen()) {
        sf::Event event;
        while (popupWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                popupWindow.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (closeButton.getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))) {
                    popupWindow.close();
                }
            }
        }
        popupWindow.clear(sf::Color::White);
        popupWindow.draw(messageText);
        closeButton.draw(popupWindow);
        popupWindow.display();
    }
}
