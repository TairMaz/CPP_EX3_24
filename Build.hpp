// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef BUILD_HPP
#define BUILD_HPP

#include <iostream>
#include <map>
#include <string>
#include "Player.hpp"
#include "Board.hpp"
using namespace std;

namespace ariel {

    class Build {
    public:
        static bool canBuySettelemnt(const map<string,unsigned int>& cards); // Checking the conditions for building a settlement
        static bool placeSettelemnt(Player& player, unsigned int place, Board& board); // Construction of a settlement
        static void haveToPlaceRoad(Player& player, unsigned int place, Board& board);
        static bool placeRoad(Player& player, unsigned int place, Board& board, bool developmentCard = false); // Construction of a road
        static void cancelRoad(Player& player, unsigned int place, Board& board);  // cancel a road in case of invalid Construction of road and settlement together
        static bool placeCity(Player& player, unsigned int place, Board& board); // Construction of a city
    };

}

#endif // BUILD_HPP