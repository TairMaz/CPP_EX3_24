# CPP_EX3_24

tairmazriv@gmail.com

## Class Hierarchy Overview:
Catan: Manages the overall game, players, turns, and main game logic.

Player: Represents a player in the game, including their resources and development cards.

Board: Represents the game board, including tiles, paths, and nodes.

Build: Handles building actions, such as placing roads and settlements.

DevelopmentCard: Manages the development cards, including buying, trading, and using them.

Demo: Beginning of a game run, where the board is randomly constructed and the game is played dynamically by player choices.

Tests: The runs are on a board where the tiles and numbers are fixed (as in the illustration in the game instructions) and the execution of the game is static.

![image](https://github.com/user-attachments/assets/a3d5a6ae-0116-4a43-a36c-0931847188b6)

## The reference in the code to tiles, roads and nodes is by numbering them all as in the attached figure.

![image](https://github.com/user-attachments/assets/e712c995-3ad0-4cb3-b42b-ff8798508c0c)


## Catan Class
The Catan class is responsible for managing the game's flow, including player turns, dice rolling, trading, and ending the game. It initializes the board and players, handles game events, and determines the winner.

players: Avector of the players in the game.

board: The board of the game, including the owner lists of the paths and nodes.

currentPlayer: The player whose turn it is now to play.

turn: the current turn, start in 0.

### Methods:

Catan(Player& p1, Player& p2, Player& p3, bool run=true): Constructor that initializes the game with three players and optionally starts the game.

~Catan(): Destructor that cleans up any dynamically allocated resources.

placeFirstRoadSettlement(const string& firstOrSecond): Handles the initial placement of roads and settlements for each player.

runGame(): Starts the game, manages the initial setup, and begins the turn rotation.

runTurn(bool first = false): Manages a player's turn, including the options to build, trade, and use development cards.

rollDice(): Simulates rolling two dice and handles the resulting actions, such as distributing resources.

chooseNum(): Securely prompts the user for a number input, ensuring valid input.

choosePlayer(): Prompts the current player to choose another player for trading or other interactions.

tradeResources(): Manages the resource trading process between players.

agreeToTrade(string playerName): Prompts a player to agree or disagree with a trade offer.

tradeDevelopmentCard(): Manages the process of trading development cards between players.

agreeToDevelopmentTrade(string playerName): Prompts a player to agree or disagree with a development card trade offer.

void nextTurn(): Advances the game to the next player's turn.

void endGame(): Ends the game and displays the final scores of all players.

## Board Class
The Board class represents the game board, including the tiles, paths, and nodes. It manages the ownership of paths and nodes and provides methods for interacting with the board.

Tiles: A vector of tiles, each represented by a pair of a resource type and a number.

pathsOwners: A vector that tracks the ownership of paths on the board.

nodesOwners: A vector that tracks the ownership of nodes on the board.

tilesAdjacentNodes: A nested vector that maps each node to its adjacent tiles.

NodesAdjacentPaths: A vector that maps each path to its adjacent nodes.

Board(bool random): Constructor of the board, if the board is random will change the position of the boards randomly.

## Player Class
The Player class represents a player in the game. Each player has a name, a collection of roads, properties (settlements and cities), resources, and development cards. The class provides methods to manage these assets, such as adding roads and properties, managing resources, and performing trades with other players. The player also has a score represented by points and knights, which contribute to winning the game. Below is a summary of the main attributes and methods:

name: The player's name.

roads: A list of roads owned by the player.

property: A map of locations on the board where the player has built settlements or cities.

accept: A map that keeps track of what resources the player receives based on dice rolls.

cards: A map of resources and their quantities.

developmentCards: A list of development cards owned by the player.

cardsCounter: The total count of resource cards the player holds.

points: The player's points, contributing to winning the game.

knights: The number of knight cards the player has played.

### Methods:

Player(string name): Constructor initializing a player with a given name.

setAccept(int at, string value): Sets the resources the player will receive for a specific dice number.

addDevelopmentCard(DevelopmentCard& newCard): Adds a new development card to the player's collection and updates points and knights accordingly.

printCards(): Prints the resources the player holds.

printDevelopmentCards(): Prints the player's development cards.

reduceCards(): Reduces the player's cards by half if a 7 is rolled on the dice.

getCards(int diceNum): Adds resources to the player based on the dice roll.

addCard(string resource, unsigned int amount): Adds a specified amount of a resource to the player's collection.

trade(Player& p, string bring, string get, unsigned int bringAmount, unsigned int getAmount): Trades resources with another player.


## Build Class
The Build class provides static methods for constructing settlements, roads, and cities on the game board. The methods ensure that players have the necessary resources and meet the conditions for construction. 

### Methods:

canBuySettelemnt(const map<string, unsigned int>& cards): Checks if the player has the necessary resources to build a settlement.

placeSettelemnt(Player& player, unsigned int place, Board& board): Attempts to place a settlement at a specified location on the board. It checks if the location is valid and if the player has the required resources.

placeRoad(Player& player, unsigned int place, Board& board, bool developmentCard = false): Attempts to place a road at a specified location on the board. It checks if the location is valid and if the player has the required resources.

cancelRoad(Player& player, unsigned int place, Board& board): Cancels the placement of a road if the construction is invalid.

placeCity(Player& player, unsigned int place, Board& board): Attempts to upgrade a settlement to a city at a specified location on the board. It checks if the player has the required resources.

haveToPlaceRoad(Player& player, unsigned int place, Board& board): Forces the player to place a road at a valid location if using a road-building development card. The player must try again until they succeed.

## DevelopmentCard Class 
The DevelopmentCard class represents a development card in a Catangame. Each card has a specific type (Monopol, Build 2 Roads, knight, victoryPoint, getResources), and players can use these cards to perform special actions during the game. The class provides functionality for picking, buying, using, and trading development cards.

### Methods:

DevelopmentCard(DevelopmentCardType t): Initializes a development card with a specific type.

pickCard(): Randomly selects and returns a development card from the available types.

canBuyDevelopmentCard(const Player& player): Checks if a player has enough resources to buy a development card.

buyDevelopmentCard(Player& player): Deducts the required resources from the player and adds a randomly picked development card to their collection.

useDevelopmentCard(Player& player, Board& board, Catan* game, bool ask=true, int cardNumber=1): Allows a player to use a development card, triggering its specific action based on the card type.

Monopol(Player& player, Catan* game, bool ask=true, string type="wheat"): Executes the Monopol card's action, allowing the player to take all of a specific resource from other players.

Build2Roads(Player& player, Board& board, bool ask=true, unsigned int place1=1, unsigned int place2=2): Executes the Build 2 Roads card's action, enabling the player to build two roads.

GetResources(Player& player): Executes the Get Resources card's action, allowing the player to choose and receive two resource cards.

trade(Player& player, Player& other, DevelopmentCardType bring, DevelopmentCardType get, unsigned int bringAmount, unsigned int getAmount): Facilitates a trade of development cards between two players.

TypeToString(DevelopmentCardType type): Converts a development card type to its corresponding string representation.

matchType(unsigned int cardType): Maps an integer to a corresponding development card type, used when a player selects a card type by number.


## Libraries used in the code:

1. <iostream>: Used for input and output operations, like cout and cin.

2. <unordered_map>: Provides a hash table-based implementation of the map, which allows for fast key-value pair lookups.

3. <vector>: Used to create dynamic arrays that can grow in size, typically for storing collections of items.

4. <chrono>: Used for time-related functions, particularly for generating a seed for the random number generator.

5. <random>: Provides facilities for random number generation, like default_random_engine and uniform_int_distribution.

6. <algorithm>: Offers a range of algorithms like find_if, count_if, and others that can be applied to containers such as vectors.

