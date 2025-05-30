//fikhman2005@gmail.com
#include "../../include/PlayerEntry.hpp"

PlayerEntry::PlayerEntry(string name,string role,sf::Font& font, float y):deleteButton(Button(600, y, 100, 40, "Delete", font, sf::Color::Red)) {
    nameText.setFont(font);
    nameText.setString(name);
    nameText.setCharacterSize(20);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(200, y);
    
    roleText.setFont(font);
    roleText.setString(role);
    roleText.setCharacterSize(20);
    roleText.setFillColor(sf::Color::Green);
    roleText.setPosition(400, y);
}
void PlayerEntry::setPosition(float y){
    nameText.setPosition(200, y);
    roleText.setPosition(400, y);
    deleteButton.setPosition(600, y);
}
void PlayerEntry::draw(sf::RenderWindow& window) const{
    window.draw(nameText);
    window.draw(roleText);
    deleteButton.draw(window);
}




