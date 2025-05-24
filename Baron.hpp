#pragma once
using std::string;

namespace coup {
    class Baron : public Player {
        public:
            Baron(Game &game, string name);
            void invest();
    };
}