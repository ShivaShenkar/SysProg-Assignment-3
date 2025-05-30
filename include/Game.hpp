//fikhman2005@gmail.com
#pragma once
#include <vector>
#include <string>
#include <stdexcept>
using std::string;
using std::vector;

namespace coup{
    class Game{
        public:
            Game();
            void add_player(string name);
            string turn() const;
            vector<string> players() const ;
            void next_turn();
            bool has_name(string name) const;
            void remove_player(string name);
            bool is_game_on() ;
            int get_turn_indexI() const;
            void set_game_active();
        private:
            vector<string> players_list;
            int current_turn;
            bool is_game_active;
            
    };
}
