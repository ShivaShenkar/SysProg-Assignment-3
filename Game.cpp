#include "Game.hpp"
#include <string>
#include <vector>
#include <stdexcept>
using std::string;
using std::vector;
namespace coup {
    Game::Game(): current_turn(0){}
    void Game::add_player(string name) {
        players_list.push_back(name);
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
        if (another_turn_flag) {
            another_turn_flag = false;
            return;
        }
        current_turn++;
        if (current_turn >= players_list.size()) {
            current_turn = 0;
        }
    }
    bool Game::has_name(string name) const {
        for (const string& player : players_list) {
            if (player == name) {
                return true;
            }
        }
        return false;
    }
    void Game::setCurrentTurn(string name) {
        for (size_t i = 0; i < players_list.size(); ++i) {
            if (players_list[i] == name) {
                current_turn = i;
                return;
            }
        }
        throw std::invalid_argument("Player not found");
    }
    void Game::remove_player(string name) {
        for (size_t i = 0; i < players_list.size(); ++i) {
            if (players_list[i] == name) {
                players_list.erase(players_list.begin() + i);
                return;
            }
        }
        throw std::invalid_argument("Player not found");
    }
}