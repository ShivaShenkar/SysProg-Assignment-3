#include "include/gui.hpp"

int main() {
    // Start the game by calling the startGame function
    GUI gui;
    try {
        gui.startGame();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Return an error code
    }
    
    return 0;
}