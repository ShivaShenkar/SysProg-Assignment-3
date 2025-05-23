class Judge : public Player {
    public:
        Judge(Game &game, string name);
        void undo_bribe(Player &target);
};