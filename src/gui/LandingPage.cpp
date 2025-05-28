#include "LandingPage.hpp"
#include <iostream>

void startGame() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game Window");

    // Load font
    sf::Font font;
    if (!font.loadFromFile("/home/lior-laptop/maarachot/assignment3/src/gui/Gloock-Regular.ttf")) {

        std::cout << "Failed to load font!" << std::endl;
        return;  // Exit if font can't be loaded
    }

    // Create text once
    sf::Text text("Game of Coup", font, 60);
    text.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
               textRect.top + textRect.height / 2.0f);
    text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
}
