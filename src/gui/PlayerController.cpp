#include "../../include/PlayerController.hpp"

PlayerController::PlayerController(Player& player,float x,float y,sf::Font& font) : player(player),font(font) {
    int labelSpacing = 150; // horizontal spacing between labels
    int buttonWidth = 85;   // Reduced width for more buttons
    int buttonSpacing = 8; // Small gap between buttons
    int maxButtons = 8;
    int buttonHeight = 40; // Increased height for better fit
    int buttonYOffset = 40; // vertical offset for buttons below info

    playerNameText.setFont(font);
    playerNameText.setString(player.name);
    playerNameText.setCharacterSize(20);
    playerNameText.setFillColor(sf::Color::Black);
    playerNameText.setPosition(x, y);

    playerCoinsText.setFont(font);
    playerCoinsText.setString("Coins: " + std::to_string(player.coins()));
    playerCoinsText.setCharacterSize(20);
    playerCoinsText.setFillColor(sf::Color::Black);
    playerCoinsText.setPosition(x + labelSpacing, y);

    playerRoleText.setFont(font);
    playerRoleText.setString("Role: " + player.type);
    playerRoleText.setCharacterSize(20);
    playerRoleText.setFillColor(sf::Color::Blue);
    playerRoleText.setPosition(x + 2 * labelSpacing, y);

    // Create action buttons based on player's role
    std::vector<string> actions = {"Gather", "Tax", "Bribe", "Arrest", "Sanction", "Coup"};
    if(player.type=="Baron") actions.push_back("invest");
    if(player.type=="Spy") {
        actions.push_back("Watch\nCoins");
        actions.push_back("Cancel\nArrest");
    }
    if(player.type=="General") actions.push_back("Coup\nImmune");
    if(player.type=="Governor"|| player.type=="Judge") actions.push_back("Undo");

    int numButtons = actions.size();
    int usedWidth = numButtons * buttonWidth + (numButtons - 1) * buttonSpacing;
    int buttonsStartX = x;
    for (int i = 0; i < numButtons; ++i) {
        int bx = buttonsStartX + i * (buttonWidth + buttonSpacing);
        actionButtons.push_back(Button(bx, y + buttonYOffset, buttonWidth, buttonHeight, actions[i], font));
    }
}

void PlayerController::draw(sf::RenderWindow& window) const {
    // Draw player information
    window.draw(playerNameText);
    window.draw(playerCoinsText);
    window.draw(playerRoleText);

    // Draw action buttons
    for (const Button& button : actionButtons) {
        button.draw(window);
    }
}