#ifndef BUILD_HPP
#define BUILD_HPP

#include <iostream>
#include <map>
#include <string>
#include "Player.hpp"
#include "Board.hpp"

namespace ariel {

    class Build {
    public:
        static bool canBuySettelemnt(const std::map<std::string,unsigned int>& cards);
        static bool placeSettelemnt(Player& player, unsigned int place, Board& board);
        static void haveToPlaceRoad(Player& player, unsigned int place, Board& board);
        static bool placeRoad(Player& player, unsigned int place, Board& board, bool developmentCard = false);
        static void cancelRoad(Player& player, unsigned int place, Board& board);
        static bool placeCity(Player& player, unsigned int place, Board& board);
    };

}

#endif // BUILD_HPP