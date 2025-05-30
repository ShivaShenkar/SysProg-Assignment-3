//fikhman2005@gmail.com

#include "../../include/gui.hpp"



void organizeList(std::vector<PlayerEntry>& playerEntries) {
    for (size_t i = 0; i < playerEntries.size(); ++i) {
        playerEntries[i].setPosition(150 + 50 * i);
    }
}

void organizeControllers(std::vector<std::unique_ptr<PlayerController>>& playerControllers) {
    for (size_t i = 0; i < playerControllers.size(); ++i) {
        float newY = 50 + 100 * i;
        playerControllers[i]->playerNameText.setPosition(50, newY);
        playerControllers[i]->playerCoinsText.setPosition(200, newY);
        playerControllers[i]->playerRoleText.setPosition(350, newY);
        auto& buttons = const_cast<std::vector<Button>&>(playerControllers[i]->getActionButtons());
        for (size_t j = 0; j < buttons.size(); ++j) {
            buttons[j].setPosition(50 + j * (85 + 8), newY + 40);
        }
    }
}

GUI::GUI() :window(sf::VideoMode(800, 600), "Game Window") {
    if (!mainFont.loadFromFile("/home/lior-laptop/maarachot/assignment3/src/gui/fonts/arial.ttf")) {
        throw std::runtime_error("Failed to load main font!"); 
    }
    if (!titleFont.loadFromFile("/home/lior-laptop/maarachot/assignment3/src/gui/fonts/Gloock-Regular.ttf")) {
        throw std::runtime_error("Failed to load title font!"); 
    }
}

void GUI::startGame() {

    // Create text once
    sf::Text titleText("Game of Coup", titleFont, 60);
    titleText.setFillColor(sf::Color::Black);
    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width / 2.0f,
               textRect.top + textRect.height / 2.0f);
    titleText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);


    sf::RectangleShape PlayButton(sf::Vector2f(200, 50));
    PlayButton.setFillColor(sf::Color::Blue);
    PlayButton.setPosition(window.getSize().x / 2.0f -PlayButton.getSize().x/2, window.getSize().y / 2.0f);


    sf::Text PlayText("Start Playing", mainFont, 20);
    PlayText.setFillColor(sf::Color::White);
    PlayText.setPosition(PlayButton.getPosition().x + 20, 
                               PlayButton.getPosition().y + 10);


    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (PlayButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    gameSettings(); 
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(titleText);
        window.draw(PlayButton);
        window.draw(PlayText);
        window.display();
    }
}

void GUI::gameSettings() {
    string roles[] = {"Baron","General","Governor","Judge","Merchant","Spy"};
    // RoleDropdown* rddPtr = nullptr;

    std::vector<PlayerEntry> playerEntries;
    playerEntries.push_back(PlayerEntry("Player 1",roles[rand() % (sizeof(roles)/sizeof(roles[0]))],mainFont,150));
    int count=2;
    int ind=2;
    

    Button addPlayerButton((window.getSize().x-200)/2, window.getSize().y / 10, 200, 50, "Add Player", mainFont);
    Button startGameButton((window.getSize().x-200)/2, window.getSize().y / 1.3f, 200, 50, "Start Game", mainFont, sf::Color::Green);
    

    
    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                
                for(int i = 0; i < playerEntries.size(); ++i) {
                    if(playerEntries[i].deleteButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))){
                        // Remove the player entry
                        playerEntries.erase(playerEntries.begin() + i);
                        organizeList(playerEntries);
                        ind--;
                        break;

                    }
                          
                }   
                if(addPlayerButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))){
                    if(ind<=5){
                        string name = "Player " + std::to_string(count++);
                        playerEntries.push_back(PlayerEntry(name, roles[rand() % (sizeof(roles)/sizeof(roles[0]))], mainFont,150+50*playerEntries.size()));
                    }
                }
                if(startGameButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))){
                    if(playerEntries.size() >= 2) {
                        gamePage(playerEntries);
                    }
                    
                }
                
            }
        }

        window.clear(sf::Color::White);
        addPlayerButton.draw(window);
        startGameButton.draw(window);
        for(const PlayerEntry& entry : playerEntries) {
            entry.draw(window);
        }
        window.display();
    }
}








void GUI::gamePage(vector<PlayerEntry>& playerEntries) {
    window.clear(sf::Color::White);
    Game game;
    std::vector<std::unique_ptr<Player>> players;
    std::vector<std::unique_ptr<PlayerController>> playerControllers;


    for(const PlayerEntry& entry : playerEntries) {
        std::string role = entry.roleText.getString().toAnsiString();
        std::string name = entry.nameText.getString().toAnsiString();
        if(role=="Baron"){
            players.push_back(std::make_unique<Baron>(game, name));
        }
        else if(role=="General"){
            players.push_back(std::make_unique<General>(game, name));
        }
        else if(role=="Governor"){
            players.push_back(std::make_unique<Governor>(game, name));
        }
        else if(role=="Judge"){
            players.push_back(std::make_unique<Judge>(game, name));
        }
        else if(role=="Merchant"){
            players.push_back(std::make_unique<Merchant>(game, name));
        }
        else if(role=="Spy"){
            players.push_back(std::make_unique<Spy>(game, name));
        }
        else {
            throw std::runtime_error("Invalid role: " + role);
        }
        playerControllers.push_back(std::make_unique<PlayerController>(*players.back(), 50, 50 + 100 * playerControllers.size(), mainFont));
    }

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                PlayerController& controller = *playerControllers[game.get_turn_indexI()];
                Player& player = controller.getPlayer();
                const vector<Button>& buttons = controller.getActionButtons();
                for (size_t j = 0; j < buttons.size(); ++j) {
                        const Button& btn = buttons[j];
                        if (btn.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                            std::string label = btn.getLabel();
                            string msg;
                            try {
                                
                                if (label == "Gather") {
                                    player.gather();
                                    controller.playerCoinsText.setString("Coins: " + std::to_string(player.coins()));
                                    std::cout << player.name << " performed Gather." << std::endl;
                                } else if (label == "Tax") {
                                    player.tax();
                                    controller.playerCoinsText.setString("Coins: " + std::to_string(player.coins()));
                                    std::cout << player.name << " performed Tax." << std::endl;
                                } else if (label == "Bribe") {
                                    if(player.coins() < 4) {
                                        msg = "You need at least 4 coins to Bribe.";
                                        PopupWindow popup("Insufficient Coins", msg, mainFont);
                                        popup.draw();
                                        continue;
                                    }
                                    player.bribe();
                                    controller.playerCoinsText.setString("Coins: " + std::to_string(player.coins()));
                                    std::cout << player.name << " performed Bribe." << std::endl;
                                }
                                else if(label=="invest"){
                                    if (auto* baron = dynamic_cast<Baron*>(&player)) {
                                        baron->invest();
                                        controller.playerCoinsText.setString("Coins: " + std::to_string(player.coins()));
                                        std::cout << player.name << " performed Invest." << std::endl;
                                    } 
                                    else {
                                        throw std::runtime_error("Only Baron can Invest.");
                                    }
                                }
                                else if(label=="Arrest"){
                                    actionInterface("Arrest", player, players,game);
                                }
                                else if(label=="Sanction"){
                                    if(player.coins()>=3){
                                        actionInterface("Sanction", player, players,game);
                                    }
                                    else{
                                        msg = "You need at least 3 coins to Sanction.";
                                        PopupWindow popup("Insufficient Coins", msg, mainFont);
                                        popup.draw();
                                    }
                                }
                                else if (label == "Coup") {
                                    size_t prevPlayerCount = players.size();
                                    if (player.coins() >= 7) {
                                        Player* target = actionInterface("Coup", player, players,game);
                                        cout<<players.size()<<endl;
                                        if (target != nullptr && game.players().size() < prevPlayerCount) {
                                            int targetIdx = -1;
                                            for (size_t i = 0; i < players.size(); ++i) {
                                                if (players[i].get()->name == target->name) {
                                                    targetIdx = i;
                                                    break;
                                                }
                                            }
                                            if (targetIdx != -1) {
                                                players.erase(players.begin() + targetIdx);
                                                playerControllers.erase(playerControllers.begin() + targetIdx);
                                                organizeControllers(playerControllers);
                                            }
                                        }
                                    }
                                    else {
                                        msg = "You need at least 7 coins to perform a Coup.";
                                        PopupWindow popup("Insufficient Coins", msg, mainFont);
                                        popup.draw();
                                    }
                                }
                                else if(label=="Coup\nImmune"){
                                    if(player.coins()>=5){
                                        actionInterface("Coup Immune", player, players,game);
                                    }
                                    else {
                                        msg = "You need at least 5 coins to perform Coup Immune.";
                                        PopupWindow popup("Insufficient Coins", msg, mainFont);
                                        popup.draw();
                                    }
                                }
                                else if(label=="Undo"){
                                    actionInterface("Undo", player, players,game);
                                }
                                else if(label=="Watch\nCoins"){
                                    actionInterface("Watch Coins", player, players,game);
                                }
                                else if(label=="Cancel\nArrest"){
                                    actionInterface("Cancel Arrest", player, players,game);
                                }
                                else {
                                    throw std::runtime_error("Unknown action: " + label);
                                }
                            } 
                            catch(const std::exception& e) {
                                string errMsg = "Error: " + std::string(e.what());
                                PopupWindow popup("Action Error", errMsg, mainFont);
                                popup.draw();
                            }
                        }
                    }
            }
        }
        window.clear(sf::Color::White);
        // Highlight current player's area in gray
        std::string currentTurn = game.turn();
        for(size_t i = 0; i < playerControllers.size(); ++i) {
            PlayerController& controller = *playerControllers[i];
            Player& player = controller.getPlayer();
            float y = 50 + 100 * i;
            if(player.name == currentTurn) {
                sf::RectangleShape highlight(sf::Vector2f(window.getSize().x, 90));
                highlight.setPosition(0, y - 10); // -10 for a little padding
                highlight.setFillColor(sf::Color(205, 180, 219)); // light gray
                window.draw(highlight);
                controller.playerCoinsText.setString("Coins: " + std::to_string(player.coins()));
            } else {
                controller.playerCoinsText.setString("");
            }
        }
        // Draw all players
        for(const auto& controller : playerControllers) {
            controller->draw(window);
        }
        window.display();

        // Check for victory condition
        if (game.players().size() == 1) {
            std::string winner = game.players()[0];
            victoryPage(winner);
            return;
        }
    }
    
}

void GUI::victoryPage(const std::string& winner) {
    window.clear(sf::Color::White);
    sf::Text victoryText("Victory!", titleFont, 60);
    victoryText.setFillColor(sf::Color::Green);
    sf::FloatRect textRect = victoryText.getLocalBounds();
    victoryText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    victoryText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 4.0f);

    sf::Text winnerText("Winner: " + winner, mainFont, 32);
    winnerText.setFillColor(sf::Color::Black);
    sf::FloatRect winnerRect = winnerText.getLocalBounds();
    winnerText.setOrigin(winnerRect.left + winnerRect.width / 2.0f, winnerRect.top + winnerRect.height / 2.0f);
    winnerText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

    Button backButton(window.getSize().x / 2.0f - 100, window.getSize().y * 0.7f, 200, 60, "Back to Main Menu", mainFont, sf::Color::Blue);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (backButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    startGame();
                    return;
                }
            }
        }
        window.clear(sf::Color::White);
        window.draw(victoryText);
        window.draw(winnerText);
        backButton.draw(window);
        window.display();
    }
}











// Show a popup for target selection and execute the action on the chosen player
Player* GUI::actionInterface(string actionName, Player& player, std::vector<std::unique_ptr<Player>>& players,Game& game) {
    // Find the current player index
    int selfIdx = -1;
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i].get() == &player) {
            selfIdx = i;
            break;
        }
    }
    if (selfIdx == -1) return nullptr; 

    // Prepare popup window
    sf::RenderWindow popup(sf::VideoMode(350, 60 + 60 * (players.size() - 1)), "Select Target");
    std::vector<Button> targetButtons;
    int btnY = 30;
    for (size_t i = 0; i < players.size(); ++i) {
        if ((int)i == selfIdx){
            if(actionName=="Coup Immune")
                targetButtons.emplace_back(50, btnY, 250, 40, players[i]->name, mainFont);
            else
                continue; // Don't allow self-target for other actions
        }
        targetButtons.emplace_back(50, btnY, 250, 40, players[i]->name, mainFont);
        btnY += 60;
    }
    Button cancelBtn(100, btnY, 120, 40, "Cancel", mainFont, sf::Color::Red);

    std::string errorMsg = "";
    bool done = false;
    while (popup.isOpen() && !done) {
        sf::Event event;
        while (popup.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                
                popup.close();
                return nullptr;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                string msg;
                sf::Vector2i mousePos = sf::Mouse::getPosition(popup);
                // Check target buttons
                int btnIdx = 0;
                for (size_t i = 0; i < players.size(); ++i) {
                    if ((int)i == selfIdx) continue;
                    if (targetButtons[btnIdx].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        // Attempt action
                        try {
                            if (actionName == "Arrest") {
                                player.arrest(*players[i]);
                                std::cout << player.name << " arrested " << players[i]->name << std::endl;

                            } else if (actionName == "Sanction") {
                                player.sanction(*players[i]);
                                std::cout << player.name << " sanctioned " << players[i]->name << std::endl;
                            } else if (actionName == "Coup") {
                                int prevPlayerCount = players.size();
                                player.coup(*players[i]);
                                std::cout << player.name << " performed Coup on " << players[i]->name << std::endl;
                                msg = (prevPlayerCount>game.players().size()) ? 
                                    players[i]->name + " has been removed from the game." : 
                                    players[i]->name + " is Immune to Coup and wasn't removed.";
                                PopupWindow popup("Coup Result", msg, mainFont);
                                popup.draw();
                            } else if (actionName == "Coup Immune") {
                                // Only General has this, dynamic_cast to General
                                if (auto* gen = dynamic_cast<General*>(&player)) {
                                    gen->coup_immune(*players[i]);
                                    std::cout << player.name << " performed Coup Immune on " << players[i]->name << std::endl;
                                } else {
                                    throw std::runtime_error("Only General can use Coup Immune");
                                }
                            } else if (actionName == "Undo") {
                                // Governor or Judge
                                if (auto* gov = dynamic_cast<Governor*>(&player)) {
                                    gov->undo(*players[i]);
                                    std::cout << player.name << " (Governor) undid action for " << players[i]->name << std::endl;
                                    msg = "Action for " + players[i]->name + " has been undone.";
                                } else if (auto* judge = dynamic_cast<Judge*>(&player)) {
                                    judge->undo(*players[i]);
                                    std::cout << player.name << " (Judge) undid action for " << players[i]->name << std::endl;
                                } else {
                                    throw std::runtime_error("Only Governor or Judge can Undo");
                                }
                            } else if (actionName == "Watch Coins") {
                                if (auto* spy = dynamic_cast<Spy*>(&player)) {
                                    int coins = spy->watchCoins(*players[i]);
                                    std::cout << player.name << " (Spy) watched " << players[i]->name << "'s coins: " << coins << std::endl;
                                    msg = players[i]->name + " has " + std::to_string(coins) + " coins.";
                                    PopupWindow popup("Watch Coins", msg, mainFont);
                                    popup.draw();
                                } else {
                                    throw std::runtime_error("Only Spy can Watch Coins");
                                }
                            } else if (actionName == "Cancel Arrest") {
                                if (auto* spy = dynamic_cast<Spy*>(&player)) {
                                    spy->cancelArrest(*players[i]);
                                    std::cout << player.name << " (Spy) canceled arrest for " << players[i]->name << std::endl;
                                    msg = "Arrest for " + players[i]->name + " has been canceled.";
                                    PopupWindow popup("Cancel Arrest", msg, mainFont);
                                    popup.draw();
                                } else {
                                    throw std::runtime_error("Only Spy can Cancel Arrest");
                                }
                            } else {
                                throw std::runtime_error("Unknown action: " + actionName);
                            }
                            done = true;
                            popup.close();
                            return players[i].get(); 
                        } catch (const std::exception& e) {
                            errorMsg = e.what();
                            return nullptr;
                        }
                        break;
                    }
                    btnIdx++;
                }
                // Cancel button
                if (cancelBtn.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    done = true;
                    popup.close();
                    return nullptr;
                }
            }
        }
        popup.clear(sf::Color(245,245,245));
        // Draw title
        sf::Text title("Select a target for " + actionName, mainFont, 20);
        title.setFillColor(sf::Color::Black);
        title.setPosition(20, 5);
        popup.draw(title);
        // Draw buttons
        for (const auto& btn : targetButtons) btn.draw(popup);
        cancelBtn.draw(popup);
        // Draw error message if any
        if (!errorMsg.empty()) {
            sf::Text err(errorMsg, mainFont, 16);
            err.setFillColor(sf::Color::Red);
            err.setPosition(20, popup.getSize().y - 30);
            popup.draw(err);
        }
        popup.display();
    }
    return nullptr;
}
