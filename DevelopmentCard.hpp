// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef DEVELOPMENTCARD_HPP
#define DEVELOPMENTCARD_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;

namespace ariel {

class Catan;

enum class DevelopmentCardType {
    Monopol,
    Build2Roads,
    GetResources,
    Knight,
    VictoryPoint
};

class Player; 
class Board; 

class DevelopmentCard {
public:
    DevelopmentCard(DevelopmentCardType t);
    DevelopmentCardType getType() const;
    static DevelopmentCard pickCard();
    static bool canBuyDevelopmentCard(const Player& player);
    static void buyDevelopmentCard(Player& player);
    static void useDevelopmentCard(Player& player, Board& board, Catan* game, bool ask=true, int cardNumber=1);
    static void Monopol(Player& player, Catan* game, bool ask=true, string type="wheat");
    static void Build2Roads(Player& player, Board& board, bool ask=true, unsigned int place1=1, unsigned int place2=2);
    static void GetResources(Player& player);
    static void trade(Player& player, Player& other, DevelopmentCardType bring, DevelopmentCardType get, unsigned int bringAmount, unsigned int getAmount);
    static string TypeToString(DevelopmentCardType type);
    static DevelopmentCardType matchType(unsigned int cardType);

private:
    DevelopmentCardType type;
};

}

#endif // DEVELOPMENTCARD_HPP
