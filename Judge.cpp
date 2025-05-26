#include "Judge.hpp"

namespace coup{
    Judge::Judge(Game &game, string name) : Player(game, name) {
        type = "Judge";
    }
    void Judge::undo(Player &target){
        if(target.bribeFlag) {
            target.bribeFlag = false;
            
        } else {
            throw std::runtime_error("The player " + target.name + " does not have an active bribe to undo");
        }
    }
    

            
}