//fikhman2005@gmail.com
#include "../include/Game.hpp"
#include <iostream>

namespace coup {
    Game::Game(): current_turn(0){}
    void Game::add_player(string name) {
        if(!is_game_on()) {
            players_list.push_back(name);
            
        }
        else
            throw std::runtime_error("Game is active, cannot add players");
        
    }
    string Game::turn() const {
        if (players_list.empty()) {
            throw std::runtime_error("No players in the game");
        }
        return players_list[current_turn];
    }
    vector<string> Game::players() const {
        return players_list;
    }
    void Game::next_turn() {
        current_turn++;
        current_turn %= players_list.size();
    }
    bool Game::has_name(string name) const {
        for (const string& player : players_list) {
            if (player == name) {
                return true;
            }
        }
        return false;
    }
    void Game::remove_player(string name) {

        for (size_t i = 0; i < players_list.size(); ++i) {
            if (players_list[i] == name) {
                players_list.erase(players_list.begin() + i);
                if(current_turn>i)
                    current_turn--;

                return;
            }
        }
        throw std::invalid_argument("Player not found");

        
    }
    bool Game::is_game_on()  {
        return is_game_active;
    }
    int Game::get_turn_indexI() const {
        return current_turn;
    }
    void Game::set_game_active() {
        is_game_active = true;
    }
}