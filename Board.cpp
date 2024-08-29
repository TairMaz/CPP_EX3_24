// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#include "Board.hpp"

namespace ariel {

Board::Board(bool random) : Tiles({{"ore", 10}, {"wool", 2}, {"wood", 9},
                                    {"wheat", 12}, {"bricks", 6}, {"wool", 4}, {"bricks", 10},
                                    {"wheat", 9}, {"wood", 11}, {"Desert", 0}, {"wood", 3}, {"ore", 8},
                                    {"wood", 8}, {"ore", 3}, {"wheat", 4}, {"wool", 5},
                                    {"bricks", 5}, {"wheat", 6}, {"wool", 11}}), pathsOwners(72, "none"), nodesOwners(54, "none") {
    // Setting up a board with random locations, for advanced players:
    if (random){
        vector<pair<string, int>> randomTiles;

        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);

        vector<string> tiles = {
            "Desert", "bricks", "bricks", "bricks",
            "ore", "ore", "ore",
            "wool", "wool", "wool", "wool",
            "wheat", "wheat", "wheat", "wheat",
            "wood", "wood", "wood", "wood"
        };
        shuffle(tiles.begin(), tiles.end(), generator);

        vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};
        shuffle(numbers.begin(), numbers.end(), generator);    

        auto numIter = numbers.begin();

        for (const auto& tile : tiles) {
            if (tile == "Desert") {      // Desert get a Impossible number in dice
                randomTiles.push_back({tile, 0});
            } else {
                randomTiles.push_back({tile, *numIter});
                ++numIter;
            }
        }
        Tiles = randomTiles;
    }
}

vector<pair<string, int>>& Board::getTiles() {
    return this->Tiles; 
}

void Board::printTiles() {
    int num = 0;
    for (const auto& pair : this->Tiles) {
        cout << num << " Tile: " << pair.first << ", Number: " << pair.second << endl;
        num++;
    }
}

vector<string>& Board::getPathsOwners() {
    return this->pathsOwners;
}

void Board::printPathsOwners() {
    for (unsigned int i = 0; i < pathsOwners.size(); i++) {
        cout << "Path: " << i << ", Owner: " << pathsOwners[i] << endl;
    }
}

vector<string>& Board::getNodesOwners() {
    return this->nodesOwners;
}

void Board::printNodesOwners() {
    for (unsigned int i = 0; i < nodesOwners.size(); i++) {
        cout << "Node: " << i << ", Owner: " << nodesOwners[i] << endl;
    }
}

vector<vector<unsigned int>>& Board::getTilesAdjacentNodes() {
    return this->tilesAdjacentNodes;
}

vector<pair<unsigned int, unsigned int>>& Board::getNodesAdjacentPaths() {
    return this->NodesAdjacentPaths;
}
}