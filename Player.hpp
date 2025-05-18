
#include "Game.hpp"
class Player
{
private:
    Game game;
    string name;
    int coins;
public:
    Player(Game &game, string name) : game(game), name(name) {
        game.add_player(name);
    }
    int coins() const { return coins; }
    void gather(){coins++;}
    void tax(){coins+=2;}
    void bribe(){coins-=3;}
    void arrest(Player &target);
    void sanction(Player &target);
    void coup(Player &target);
    ~Player();  
};
