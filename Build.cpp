// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#include "Build.hpp"

namespace ariel {

    bool Build::canBuySettelemnt(const map<string, unsigned int>& cards) {
        return cards.at("wood") > 0 && cards.at("bricks") > 0 && cards.at("wool") > 0 && cards.at("wheat") > 0;
    }

    bool Build::placeSettelemnt(Player& player, unsigned int place, Board& board) {
        if (place < 0 || place > 53) {
            cout << "The number is out of range, it should be between 0 to 53" << endl;
            return false;
        } 
        //Checking that the player is allowed to build a settlement:
        else if (player.getProperty().size() < 2 || canBuySettelemnt(player.getCards())) {
            bool cond = true;
            bool cond2 = false;
            unsigned int path = 0;
            for (const auto& pair : board.getNodesAdjacentPaths()) {

                // Checking that there is no settlement at a adjacent node:
                if (((pair.first == place) && (board.getNodesOwners().at(pair.second) != "none")) ||
                    ((pair.second == place) && (board.getNodesOwners().at(pair.first) != "none"))) {
                    cond = false;
                    cout << "Invalid move, a Settlement already exists at the adjacent node" << endl;
                    return false;
                }

                // Checking that there is a path that leads to the desired location for the settlement:
                if (((pair.first == place) && (board.getPathsOwners().at(path) == player.getName())) ||
                    ((pair.second == place) && (board.getPathsOwners().at(path) == player.getName()))) {
                    cond2 = true;
                }
                path++;
            }

            if (board.getNodesOwners().at(place) != "none") {
                cond = false;
                cout << "Invalid move, a settlement already exists at the selected node" << endl;
                return false;
            }

            if (cond && cond2) {
                if (player.getProperty().size() > 2) {
                    player.getCards()["wood"]--;
                    player.getCards()["bricks"]--;
                    player.getCards()["wool"]--;
                    player.getCards()["wheat"]--;
                    player.getCardsCounter() -= 4;
                }
                // Updating the appropriate new details after the settlement was established:
                board.getNodesOwners()[place] = player.getName();
                for (unsigned int tile : board.getTilesAdjacentNodes().at(place)) {
                    player.setAccept(board.getTiles()[tile].second, board.getTiles()[tile].first);
                    if (player.getProperty().size() == 1) {
                        if (board.getTiles()[tile].second != 0){
                            player.getCards()[board.getTiles()[tile].first]++;
                            player.getCardsCounter() += 1;
                        }
                    }
                }
                player.getProperty()[place] = "settlement";
                player.getPoints() += 1;
                cout << "The settlement was successfully established" << endl;
                return true;
            }

            if (!cond2) {
                cout << "Invalid move, the player does not have a road that leads to the node" << endl;
                return false;
            }
        } else {
            cout << "The player does not have the appropriate cards to purchase" << endl;
        }
        return false;
    }

    void Build::haveToPlaceRoad(Player& player, unsigned int place, Board& board) {
        //If the player tries to place a path in an illegal place, he will have to try again and again until he succeeds
        // this is in case he is using a road building development card
        if (!placeRoad(player, place, board, true)) {
            cout << "The road is not established, Try again" << endl;
            cin >> place;
            haveToPlaceRoad(player, place, board);
        }
    }

    bool Build::placeRoad(Player& player, unsigned int place, Board& board, bool developmentCard) {
        if (place < 0 || place > 71) {
            cout << "The number is out of range, it should be between 0 to 71, try again" << endl;
            return false;
        } else if (board.getPathsOwners().at(place) != "none") {
            cout << "Invalid move, a road already exists at the selected location" << endl;
            return false;
        }
        bool cond = (player.getRoads().size() < 2);
        // Checking that that player has an adjacent road
        for (auto road : player.getRoads()) {
            if ((board.getNodesAdjacentPaths().at(road).first == board.getNodesAdjacentPaths().at(place).first) ||
                (board.getNodesAdjacentPaths().at(road).first == board.getNodesAdjacentPaths().at(place).second) ||
                (board.getNodesAdjacentPaths().at(road).second == board.getNodesAdjacentPaths().at(place).first) ||
                (board.getNodesAdjacentPaths().at(road).second == board.getNodesAdjacentPaths().at(place).second)) {
                cond = true;
            }
        }
        if ((player.getCards()["wood"] >= 1 && player.getCards()["bricks"] >= 1) || player.getRoads().size() < 2 || developmentCard) {
            if (cond) {
                // Updating the changes following the construction of the path:
                if (player.getRoads().size() >= 2 && !developmentCard) {
                    player.getCards()["wood"]--;
                    player.getCards()["bricks"]--;
                    player.getCardsCounter() -= 2;
                }
                player.getRoads().push_back(place);
                board.getPathsOwners()[place] = player.getName();
                cout << "The road was successfully established" << endl;
                return true;
            } else {
                cout << "The player does not have a road near the selected location" << endl;
                return false;
            }
        } else {
            cout << "The player does not have the appropriate cards to purchase" << endl;
        }
        return false;
    }

    void Build::cancelRoad(Player& player, unsigned int place, Board& board) {
        auto& roads = player.getRoads();
        auto it = find(roads.begin(), roads.end(), place);

        if (it != roads.end()) {
            roads.erase(it);
            board.getPathsOwners()[place] = "none";
        } else {
            cout << "The player does not have a road at the specified location." << endl;
        }
    }

    bool Build::placeCity(Player& player, unsigned int place, Board& board) {
        if (player.getCards()["ore"] >= 3 && player.getCards()["wheat"] >= 2) {
            // checking the player has a settlement in this place:
            if (board.getNodesOwners().at(place) == player.getName()) {
                // Updating the changes following the construction of the city:
                player.getCards()["ore"] -= 3;
                player.getCards()["wheat"] -= 2;
                player.getCardsCounter() -= 5;
                player.getProperty()[place] = "city";
                for (auto tile : board.getTilesAdjacentNodes().at(place)) {
                    // Updating the list of resources that the player gets for each number that comes out on the dice:
                    player.setAccept(board.getTiles()[tile].second, board.getTiles()[tile].first);
                }
                player.getPoints() += 1;
                cout << "The city was successfully established" << endl;
                return true;
            } else {
                cout << "Invalid move, there is no existing settlement at this node" << endl;
                return false;
            }
        } else {
            cout << "The player does not have the appropriate cards to purchase" << endl;
            return false;
            }
    }
}
