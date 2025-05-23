#include "Player.hpp"
class General:public Player{
    public:
        General(Game &game, string name);
        void coup_immune(Player &target);
};