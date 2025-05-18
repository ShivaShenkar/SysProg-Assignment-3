#include <string>

class Game{
    public:
        Game(){
            this->current_turn=0;
        }
        ~Game(){
        };
        void add_player(string name){
            players_list.push_back(name);
        }
        void remove_player(Player& player){
            
        }
        string turn() const{return players_list[current_turn];}
        vector<string> players() const{return players_list;}
        void next_turn(){
            if(another_turn_flag){
                another_turn_flag = false;
                return;
            }
            current_turn++;
            if(current_turn >= players_list.size()){
                current_turn = 0;
            }
        }
    private:
        vector<string> players_list;
        int current_turn;
        bool another_turn_flag;
};
