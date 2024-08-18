#ifndef BOARD_HPP
#define BOARD_HPP

#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>

using namespace std;
namespace ariel {

class Player;    

class Board {
private:
    vector<pair<string, int>> Tiles;
    vector<string> pathsOwners;
    vector<string> nodesOwners;

    vector<vector<unsigned int>> tilesAdjacentNodes{
        {0}, {0}, {0,1}, {1}, {1,2}, {2}, {2},
        {3}, {0,3}, {0,3,4}, {0,1,4}, {1,4,5}, {1,2,5}, {2,5,6}, {2,6}, {6},
        {7}, {3,7}, {3,7,8}, {3,4,8}, {4,8,9}, {4,5,9}, {5,9,10}, {5,6,10}, {6,10,11}, {6,11}, {11},
        {7}, {7,12}, {7,8,12}, {8,12,13}, {8,9,13}, {9,13,14}, {9,10,14}, {10,14,15}, {10,11,15}, {11,15}, {11},
        {12}, {12,16}, {12,13,16}, {13,16,17}, {13,14,17}, {14,17,18}, {14,15,18}, {15,18}, {15},
        {16}, {16}, {16,17}, {17}, {17,18}, {18}, {18}};

    vector<pair<unsigned int, unsigned int>> NodesAdjacentPaths{
        {0,1},{1,2}, {2,3}, {3,4}, {4,5}, {5,6},
        {0,8}, {2,10}, {4,12}, {6,14},
        {7,8}, {8,9}, {9,10}, {10,11}, {11,12}, {12,13}, {13,14}, {14,15},
        {7,17}, {9,19}, {11,21}, {13,23}, {15,25},
        {16,17}, {17,18}, {18,19}, {19,20}, {20,21},{21,22}, {22,23}, {23,24}, {24,25}, {25,26},
        {16,27}, {18,29}, {20,31}, {22,33}, {24,35}, {26,37},
        {27,28}, {28,29}, {29,30}, {30,31}, {31,32}, {32,33}, {33,34}, {34,35}, {35,36}, {36,37},
        {28,38}, {30,40}, {32,42}, {34,44}, {36,46},
        {38,39}, {39,40}, {40,41}, {41,42}, {42,43}, {43,44}, {44,45}, {45,46},
        {39,47}, {41,49}, {43,51}, {45,53},
        {47,48}, {48,49}, {49,50}, {50,51}, {51,52}, {52,53}
};

public:
//Building a new game board, by default the board is not random:
    Board(bool ramdom = false);              
    
    vector<pair<string, int>>& getTiles();  //Each pair represents a tile according to the position, each tile has the type and number
    void printTiles();
    vector<string>& getPathsOwners();
    void printPathsOwners();
    vector<string>& getNodesOwners();
    void printNodesOwners();
    vector<vector<unsigned int>>& getTilesAdjacentNodes();
    vector<pair<unsigned int, unsigned int>>& getNodesAdjacentPaths();
};

}
#endif // BOARD_HPP