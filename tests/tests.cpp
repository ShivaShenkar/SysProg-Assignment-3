//fikhman2005@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/Governor.hpp"
#include "../include/Baron.hpp"
#include "../include/General.hpp"
#include "../include/Judge.hpp"
#include "../include/Merchant.hpp"
#include "../include/Spy.hpp"
#include <stdexcept>
#include <iostream>

using namespace coup;
using namespace std;

TEST_CASE("Player and Game Initialization") {
    Game game;
    Governor gov(game, "Alice");
    CHECK_THROWS(gov.gather()); // Only one player, game not started
    CHECK_THROWS(Baron(game, "Alice")); // Duplicate name
    Baron baron(game, "Bob");
    General gen(game, "Carol");
    Judge judge(game, "Dave");
    Merchant merchant(game, "Eve");
    Spy spy(game, "Frank");
    CHECK(game.turn() == "Alice");
    CHECK(game.players().size() == 6);
    CHECK(game.players()[0] == "Alice");
    CHECK(game.players()[1] == "Bob");
    CHECK(game.players()[2] == "Carol");
    CHECK(game.players()[3] == "Dave");
    CHECK(game.players()[4] == "Eve");
    CHECK(game.players()[5] == "Frank");
    gov.gather();
    CHECK(game.turn() == "Bob");
    baron.gather();
    CHECK(game.turn() == "Carol");
    gen.gather();
    CHECK(game.turn() == "Dave");
    judge.gather();
    CHECK(game.turn() == "Eve");
    merchant.gather();
    CHECK(game.turn() == "Frank");


    CHECK_THROWS_AS(Governor(game, "Alice"), std::invalid_argument); // duplicate name
    // Can't add after game started
    gov.gather();
    CHECK_THROWS_AS(Baron(game, "NewGuy"), std::invalid_argument);
}

TEST_CASE("Turn and Action Rules, Out-of-Turn, Undo, and Turn Order") {
    Game game;
    Governor gov(game, "Alice");
    Baron baron(game, "Bob");
    Judge judge(game, "Dave");
    Merchant merchant(game, "Eve");


    // Out of turn
    CHECK_THROWS_AS(baron.gather(), std::runtime_error);
    CHECK_THROWS_AS(judge.gather(), std::runtime_error);
    CHECK_THROWS_AS(merchant.gather(), std::runtime_error);
    gov.gather();
    CHECK_NOTHROW(baron.gather());
    CHECK_NOTHROW(judge.gather());
    CHECK_NOTHROW(merchant.gather());
    gov.gather();

    // Only Judge/Governor can undo
    CHECK_THROWS_AS(baron.undo(gov), std::runtime_error);
    baron.tax();
    int coins = baron.coins();
    CHECK_THROWS_AS(merchant.undo(baron), std::runtime_error);
    CHECK_NOTHROW(gov.undo(baron));
    CHECK(coins==baron.coins()+2);
    judge.bribe();
    CHECK_THROWS_AS(judge.undo(judge),std::runtime_error);
    judge.tax();
    judge.tax();
    CHECK_NOTHROW(gov.undo(judge));
    CHECK_THROWS(gov.undo(judge));
    merchant.addCoins(4);
    merchant.bribe();
    CHECK_NOTHROW(merchant.gather());
    CHECK_NOTHROW(judge.undo(merchant));
    CHECK_THROWS(merchant.gather());
    gov.tax();
    CHECK_THROWS(judge.undo(gov));
    baron.gather();
    CHECK_THROWS(gov.undo(baron));

    // Turn order after removal
    judge.addCoins(7);
    CHECK_THROWS(judge.coup(judge));
    CHECK_NOTHROW(judge.coup(merchant));
    CHECK_THROWS(merchant.gather());
    CHECK(game.turn()=="Alice");
    CHECK(game.players().size() == 3);
    CHECK(game.turn() == "Eve");

    //sanction is implied only for one turn
    gov.addCoins(3);
    gov.sanction(baron);
    CHECK_THROWS(baron.gather());
    CHECK_THROWS(baron.tax());
    baron.arrest(gov);
    judge.gather();
    gov.gather();
    baron.addCoins(4);
    baron.bribe();
    CHECK_NOTHROW(baron.gather());
    CHECK_NOTHROW(baron.tax());
}

TEST_CASE("Coin and Action Economy, Negative Coins, and Special Role Actions") {
    Game game;
    Governor gov(game, "Alice");
    Baron baron(game, "Bob");
    Merchant merchant(game, "Eve");
    Judge judge(game,"Mike");
    // Gather, Tax, Bribe
    gov.gather();
    CHECK(gov.coins() == 1);
    baron.addCoins(4);
    baron.bribe();
    CHECK(baron.coins() == 0);
    // Bribe twice in a row
    CHECK_THROWS_AS(baron.bribe(), std::runtime_error);
    // Baron invest
    baron.gather();
    baron.addCoins(2);
    baron.invest();
    CHECK(baron.coins() == 6);
    // Merchant bonus
    merchant.addCoins(3);
    CHECK(merchant.coins() == 3);
    merchant.gather(); // Should get bonus
    CHECK(merchant.coins() == 5);
    judge.gather();
    gov.tax();
    CHECK(gov.coins() == 4);
    // Negative coins not possible
    baron.removeCoins(4);
    CHECK_THROWS_AS(baron.sanction(gov), std::runtime_error); // Not enough coins
    merchant.removeCoins(2);
    CHECK_THROWS(merchant.sanction(judge));
    CHECK_THROWS(merchant.sanction(gov));

    judge.addCoins(1);
    CHECK_THROWS(judge.sanction(judge));
    CHECK_THROWS(judge.sanction(baron));
    
    gov.addCoins(10);
    CHECK_THROWS(gov.gather());
    CHECK_THROWS(gov.tax());
    CHECK_THROWS(gov.bribe());
    CHECK_THROWS(gov.arrest(baron));
    CHECK_THROWS(gov.sanction(baron));
    CHECK_NOTHROW(gov.coup(baron));

    Game game2;
    Governor gov1(game2,"gov1");
    Governor gov2(game2,"gov2");

    gov1.tax();
    gov2.undo(gov1);
    CHECK(gov1.coins()==0);

}

TEST_CASE("Coup, Coup Immune, and Player Removal") {
    Game game;
    General gen(game, "Carol");
    Baron baron(game, "Bob");
    gen.addCoins(7);
    gen.coup(baron);
    CHECK(game.players().size() == 1); // Only Carol remains
    // Coup immune
    Baron baron2(game, "Bob2");
    gen.addCoins(12);
    gen.coup_immune(baron2);
    CHECK(baron2.isCoupImmune);
    gen.coup(baron2);
    CHECK_FALSE(baron2.isCoupImmune);
    // Coup immune on self
    gen.coup_immune(gen);
    CHECK(gen.isCoupImmune);
    baron2.gather();
    baron2.addCoins(7);
    baron2.coup(gen);
    CHECK_FALSE(gen.isCoupImmune);
}

TEST_CASE("Sanction, Arrest, and Special Interactions") {
    Game game;
    Governor gov(game, "Alice");
    Baron baron(game, "Bob");
    Judge judge(game, "Dave");
    Merchant merchant(game, "Eve");
    General gen(game, "Carol");
    // Sanctioned baron gets 1 coin
    for(int i=0;i<3;++i) gov.gather();
    gov.sanction(baron);
    CHECK(baron.coins() == 1);
    // Sanctioned judge costs 4 coins
    for(int i=0;i<4;++i) gov.gather();
    gov.sanction(judge);
    CHECK(gov.coins() == 0);
    // Sanctioned player regains after 1 turn
    for(int i=0;i<3;++i) judge.gather();
    gov.sanction(judge);
    baron.gather();
    judge.gather(); // Should be able to gather again
    // Arrest cannot be used on same player twice
    for(int i=0;i<3;++i) baron.gather();
    gov.arrest(baron);
    gov.gather();
    CHECK_THROWS_AS(gov.arrest(baron), std::runtime_error);
    // Arrest cannot be used if cancel arrest was used
    Spy spy(game, "Frank");
    spy.cancelArrest(baron);
    gov.gather();
    CHECK_THROWS_AS(gov.arrest(baron), std::runtime_error);
    // General gets coin back if arrested
    for(int i=0;i<3;++i) gen.gather();
    gov.arrest(gen);
    CHECK(gen.coins() == 3);
    // Merchant arrested with 2 coins
    for(int i=0;i<2;++i) merchant.gather();
    gov.arrest(merchant);
    CHECK(merchant.coins() == 0);
    // Merchant arrested with 0 coins
    CHECK_NOTHROW(gov.arrest(merchant));
}

TEST_CASE("Spy Actions and Multiple Targets") {
    Game game;
    Spy spy(game, "Frank");
    Baron baron(game, "Bob");
    Governor gov(game, "Alice");
    for(int i=0;i<3;++i) baron.gather();
    for(int i=0;i<3;++i) gov.gather();
    CHECK(spy.watchCoins(baron) == 3);
    CHECK(spy.watchCoins(gov) == 3);
    spy.cancelArrest(baron);
    spy.cancelArrest(gov);
    // Spy can act after using abilities
    spy.gather();
    CHECK(spy.coins() == 1);
}

TEST_CASE("Targeted Actions on Nonexistent Players and Self") {
    Game game;
    Governor gov(game, "Alice");
    Baron baron(game, "Bob");
    Judge judge(game, "Dave");
    Merchant merchant(game, "Eve");
    General gen(game, "Carol");
    Spy spy(game, "Frank");
    // Remove Bob
    for(int i=0;i<7;++i) gov.gather();
    gov.coup(baron);
    CHECK_THROWS_AS(gov.arrest(baron), std::runtime_error);
    CHECK_THROWS_AS(gov.sanction(baron), std::runtime_error);
    CHECK_THROWS_AS(gov.coup(baron), std::runtime_error);
    CHECK_THROWS_AS(gov.undo(baron), std::runtime_error);
    CHECK_THROWS_AS(gen.coup_immune(baron), std::runtime_error);
    CHECK_THROWS_AS(spy.watchCoins(baron), std::runtime_error);
    CHECK_THROWS_AS(spy.cancelArrest(baron), std::runtime_error);
    // Cannot target self (except coup immune)
    CHECK_THROWS_AS(gov.arrest(gov), std::runtime_error);
    CHECK_THROWS_AS(gov.sanction(gov), std::runtime_error);
    CHECK_THROWS_AS(gov.coup(gov), std::runtime_error);
    CHECK_THROWS_AS(gov.undo(gov), std::runtime_error);
    CHECK_THROWS_AS(spy.watchCoins(spy), std::runtime_error);
    CHECK_THROWS_AS(spy.cancelArrest(spy), std::runtime_error);
    CHECK_NOTHROW(gen.coup_immune(gen));
}

TEST_CASE("Game End and Solo Player Restrictions") {
    Game game;
    Governor gov(game, "Alice");
    for(int i=0;i<10;++i) gov.gather();
    // Remove all but one
    for(int i=0;i<7;++i) gov.gather();
    Baron baron(game, "Bob");
    for(int i=0;i<7;++i) gov.gather();
    gov.coup(baron);
    CHECK(game.players().size() == 1);
    // Only player left cannot act
    CHECK_THROWS_AS(gov.gather(), std::runtime_error);
    CHECK_THROWS_AS(gov.tax(), std::runtime_error);
    CHECK_THROWS_AS(gov.bribe(), std::runtime_error);
    CHECK_THROWS_AS(gov.sanction(gov), std::runtime_error);
    CHECK_THROWS_AS(gov.arrest(gov), std::runtime_error);
    CHECK_THROWS_AS(gov.coup(gov), std::runtime_error);
}




