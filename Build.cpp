#include "Build.hpp"

namespace ariel {

    bool Build::canBuySettelemnt(const std::map<std::string, unsigned int>& cards) {
        return cards.at("wood") > 0 && cards.at("bricks") > 0 && cards.at("wool") > 0 && cards.at("wheat") > 0;
    }

    bool Build::placeSettelemnt(Player& player, unsigned int place, Board& board) {
        if (place < 0 || place > 53) {
            std::cout << "The number is out of range, it should be between 0 to 53" << std::endl;
            return false;
        } else if (player.getProperty().size() < 2 || canBuySettelemnt(player.cards)) {
            bool cond = true;
            bool cond2 = false;
            unsigned int path = 0;
            for (const auto& pair : board.getNodesAdjacentPaths()) {
                if (((pair.first == place) && (board.getNodesOwners().at(pair.second) != "none")) ||
                    ((pair.second == place) && (board.getNodesOwners().at(pair.first) != "none"))) {
                    cond = false;
                    std::cout << "Invalid move, a Settlement already exists at the adjacent node" << std::endl;
                    return false;
                }

                if (((pair.first == place) && (board.getPathsOwners().at(path) == player.getName())) ||
                    ((pair.second == place) && (board.getPathsOwners().at(path) == player.getName()))) {
                    cond2 = true;
                }
                path++;
            }

            if (board.getNodesOwners().at(place) != "none") {
                cond = false;
                std::cout << "Invalid move, a settlement already exists at the selected node" << std::endl;
                return false;
            }

            if (cond && cond2) {
                if (player.getProperty().size() > 2) {
                    player.cards["wood"]--;
                    player.cards["bricks"]--;
                    player.cards["wool"]--;
                    player.cards["wheat"]--;
                    player.getCardsCounter() -= 4;
                }
                board.getNodesOwners()[place] = player.getName();
                for (unsigned int tile : board.getTilesAdjacentNodes().at(place)) {
                    player.setAccept(board.getTiles()[tile].second, board.getTiles()[tile].first);
                    if (player.getProperty().size() == 1) {
                        if (board.getTiles()[tile].second != 0){
                            player.cards[board.getTiles()[tile].first]++;
                            player.getCardsCounter() += 1;
                        }
                    }
                }
                player.getProperty()[place] = "settlement";
                player.getPoints() += 1;
                std::cout << "The settlement was successfully established" << std::endl;
                return true;
            }

            if (!cond2) {
                std::cout << "Invalid move, the player does not have a road that leads to the node" << std::endl;
                return false;
            }
        } else {
            std::cout << "The player does not have the appropriate cards to purchase" << std::endl;
        }
        return false;
    }

    void Build::haveToPlaceRoad(Player& player, unsigned int place, Board& board) {
        if (!placeRoad(player, place, board, true)) {
            std::cout << "The road is not established, Try again" << std::endl;
            std::cin >> place;
            haveToPlaceRoad(player, place, board);
        }
    }

    bool Build::placeRoad(Player& player, unsigned int place, Board& board, bool developmentCard) {
        if (place < 0 || place > 71) {
            std::cout << "The number is out of range, it should be between 0 to 71, try again" << std::endl;
            return false;
        } else if (board.getPathsOwners().at(place) != "none") {
            std::cout << "Invalid move, a road already exists at the selected location" << std::endl;
            return false;
        }
        bool cond = (player.getRoads().size() < 2);
        for (auto road : player.getRoads()) {
            if ((board.getNodesAdjacentPaths().at(road).first == board.getNodesAdjacentPaths().at(place).first) ||
                (board.getNodesAdjacentPaths().at(road).first == board.getNodesAdjacentPaths().at(place).second) ||
                (board.getNodesAdjacentPaths().at(road).second == board.getNodesAdjacentPaths().at(place).first) ||
                (board.getNodesAdjacentPaths().at(road).second == board.getNodesAdjacentPaths().at(place).second)) {
                cond = true;
            }
        }
        if ((player.cards["wood"] >= 1 && player.cards["bricks"] >= 1) || player.getRoads().size() < 2 || developmentCard) {
            if (cond) {
                if (player.getRoads().size() >= 2 && !developmentCard) {
                    player.cards["wood"]--;
                    player.cards["bricks"]--;
                    player.getCardsCounter() -= 2;
                }
                player.getRoads().push_back(place);
                board.getPathsOwners()[place] = player.getName();
                std::cout << "The road was successfully established" << std::endl;
                return true;
            } else {
                std::cout << "The player does not have a road near the selected location" << std::endl;
                return false;
            }
        } else {
            std::cout << "The player does not have the appropriate cards to purchase" << std::endl;
        }
        return false;
    }

      void Build::cancelRoad(Player& player, unsigned int place, Board& board) {
        auto& roads = player.getRoads();
        auto it = std::find(roads.begin(), roads.end(), place);

        if (it != roads.end()) {
            roads.erase(it);
            board.getPathsOwners()[place] = "none";
        } else {
            std::cout << "The player does not have a road at the specified location." << std::endl;
        }
    }

    bool Build::placeCity(Player& player, unsigned int place, Board& board) {
        if (player.cards["ore"] >= 3 && player.cards["wheat"] >= 2) {
            if (board.getNodesOwners().at(place) == player.getName()) {
                player.cards["ore"] -= 3;
                player.cards["wheat"] -= 2;
                player.getCardsCounter() -= 5;
                player.getProperty()[place] = "city";
                for (auto tile : board.getTilesAdjacentNodes().at(place)) {
                    player.setAccept(board.getTiles()[tile].second, board.getTiles()[tile].first);
                }
                player.getPoints() += 1;
                std::cout << "The city was successfully established" << std::endl;
                return true;
            } else {
                std::cout << "Invalid move, there is no existing settlement at this node" << std::endl;
                return false;
            }
        } else {
            std::cout << "The player does not have the appropriate cards to purchase" << std::endl;
            return false;
            }
    }
}
