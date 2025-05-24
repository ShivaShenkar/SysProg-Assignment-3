#pragma once
#include <vector>
#include <string>
using std::string;
using std::vector;

namespace coup{
    class Game{
        public:
            Game();
            ~Game();
            void add_player(string name);
            string turn() const;
            vector<string> players() const ;
            void next_turn();
            bool has_name(string name) const;
            void setCurrentTurn(string name);
            void remove_player(string name);
        private:
            vector<string> players_list;
            int current_turn;
            bool another_turn_flag;
            
    };
}
