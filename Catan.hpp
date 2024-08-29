// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef CATAN_HPP
#define CATAN_HPP

#include "Player.hpp"
#include "Board.hpp"
#include "Build.hpp"
#include "DevelopmentCard.hpp"
#include <random>
#include <vector>
#include <chrono>
#include <string>
#include <iostream>
#include <memory>  

using namespace std;

namespace ariel {

class Catan {
private:
    vector<reference_wrapper<Player>> players;
    unique_ptr<Board> board;  // use of unique_ptr to manage the memory of Board
    reference_wrapper<Player> currentPlayer;
    unsigned int turn = 0;

public:
    Catan(Player& p1, Player& p2, Player& p3, bool run=true);
    ~Catan();  

    vector<reference_wrapper<Player>> getPlayers();
    Board& getBoard();
    reference_wrapper<Player> getCurrentPlayer();

    void placeFirstRoadSettlement(const string& firstOrSecond);
    void runGame();
    void runTurn(bool first = false);
    int rollDice();
    unsigned int chooseNum();
    Player& choosePlayer();
    void tradeResources();
    bool agreeToTrade(string playerName);
    void tradeDevelopmentCard();
    bool agreeToDevelopmentTrade(string playerName);
    void nextTurn();
    void endGame();
};

}

#endif // CATAN_HPP
