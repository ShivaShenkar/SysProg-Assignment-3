
#include "Game.hpp"
class Player
{
private:
    int playerCoins;
    string name;
    bool isSanctioned;
    bool arrestFunctionFlag;
    bool coupImmune;
    string lastArrested;
    string lastAction;
    

protected:
    string type;
    Game game;
    virtual void setSanctioned();
public:
    Player(Game &game, string name);
    Player(const Player &other);
    Player &operator=(const Player &other);
    int coins() const;
    void gather();
    virtual void tax();
    void bribe();
    void arrest(Player &target);
    void sanction(Player &target);
    void coup(Player &target);
    string getName() const;
    ~Player();
    void addCoins(int coins);
    void removeCoins(int coins);  
    void setCanceledArrest();
    void setCoupImmune();
    string getType() const;
    void undo(Player &target);
    string getLastAction() const;
};
