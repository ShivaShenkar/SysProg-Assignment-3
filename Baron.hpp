class Baron : public Player {
    public:
        Baron(Game &game, string name);
        ~Baron();
        Baron(const Baron &other);
        void invest();
};