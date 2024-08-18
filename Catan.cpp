#include "Catan.hpp"

namespace ariel {

Catan::Catan(Player& p1, Player& p2, Player& p3, bool run)
    : players{p1, p2, p3}, board(nullptr), currentPlayer(p1) {

    if (run) {
        board = make_unique<Board>(true);  
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        shuffle(players.begin(), players.end(), generator);    
        currentPlayer = players[0];
        runGame();
    }
    else {
        board = make_unique<Board>(false);  
    }
}

Catan::~Catan() {}

vector<reference_wrapper<Player>> Catan::getPlayers() {
    return this->players; 
}

Board& Catan::getBoard(){
    return *(this->board); 
}

reference_wrapper<Player> Catan::getCurrentPlayer(){
    return this->currentPlayer.get();
}

void Catan::placeFirstRoadSettlement(const string& firstOrSecond) {
    try {
        unsigned int road;
        unsigned int settlement;

        cout << currentPlayer.get().getName() << " Where would you like to place your " << firstOrSecond << " road? ";
        if (!(cin >> road)) {
            throw invalid_argument("Invalid input for road location.");
        }

        cout << currentPlayer.get().getName() << " Where would you like to place your " << firstOrSecond << " settlement? ";
        if (!(cin >> settlement)) {
            throw invalid_argument("Invalid input for settlement location.");
        }

        if (board->getNodesAdjacentPaths()[road].first == settlement ||
            board->getNodesAdjacentPaths()[road].second == settlement) {
            bool roadPlaced = Build::placeRoad(currentPlayer, road, *board);
            bool settlementPlaced = Build::placeSettelemnt(currentPlayer, settlement, *board);

            if (!roadPlaced || !settlementPlaced) {
                if (roadPlaced && !settlementPlaced) {
                    Build::cancelRoad(currentPlayer, road, *board);
                    cout << "The road has been cancelled" << endl;
                }
                placeFirstRoadSettlement(firstOrSecond);
            }
        } else {
            cout << "The road and the settlement are not adjacent. Try again" << endl;
            placeFirstRoadSettlement(firstOrSecond);
        }
    } catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        placeFirstRoadSettlement(firstOrSecond);
    } catch (const exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
        placeFirstRoadSettlement(firstOrSecond);
    }
}

void Catan::runGame() {
    cout << "This is the board:" << endl;
    // board->printTiles();
    // placeFirstRoadSettlement("first");
    // nextTurn();
    // placeFirstRoadSettlement("first");
    // nextTurn();
    // placeFirstRoadSettlement("first");
    // nextTurn();
    // placeFirstRoadSettlement("second");
    // nextTurn();
    // placeFirstRoadSettlement("second");
    // nextTurn(); 
    // placeFirstRoadSettlement("second");
    // nextTurn();
    players[0].get().addCard("wheat", 5);
    players[0].get().addCard("ore", 5);
    players[0].get().addCard("wood", 5);
    players[0].get().addCard("wool", 5);    
    players[0].get().addCard("bricks", 5);
    players[1].get().addCard("wheat", 5);
    players[1].get().addCard("ore", 5);
    players[1].get().addCard("wood", 5);
    players[1].get().addCard("wool", 5);    
    players[1].get().addCard("bricks", 5);
        players[2].get().addCard("wheat", 5);
    players[2].get().addCard("ore", 5);
    players[2].get().addCard("wood", 5);
    players[2].get().addCard("wool", 5);    
    players[2].get().addCard("bricks", 5);    
    runTurn(true);
}

void Catan::runTurn(bool first) {
    Player* p = nullptr;
    if (players[0].get().getPoints() < 10 && players[1].get().getPoints() < 10 && players[2].get().getPoints() < 10) {
        int choice;
        if (first) {
            rollDice();
            cout << currentPlayer.get().getName() << " It's your turn, What would you like to do?" << endl;
        } else {
            cout << currentPlayer.get().getName() << " What would you like to do now?" << endl;
        }
        cout << "1 -  Build road" << endl;
        cout << "2 -  Build settlement" << endl;
        cout << "3 -  Build city" << endl;
        cout << "4 -  Buy development card" << endl;
        cout << "5 -  Trade resources" << endl;
        cout << "6 -  Trade development cards" << endl;
        cout << "7 -  Use development card" << endl;
        cout << "8 -  Print board" << endl;
        cout << "9 -  Print paths owners" << endl;
        cout << "10 - Print nodes owners" << endl;
        cout << "11 - Print player cards" << endl;
        cout << "12 - Print my development cards" << endl;
        cout << "13 - End turn" << endl;
        cout << "14 - End game" << endl;

        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Where would you like to place your road?" << endl;
            Build::placeRoad(currentPlayer, chooseNum(), *board);
            runTurn();
        
        case 2:
            cout << "Where would you like to place your settlement?" << endl;
            Build::placeSettelemnt(currentPlayer, chooseNum(), *board);
            runTurn();                
            break;

        case 3:
            cout << "Where would you like to place your city?" << endl;
            Build::placeCity(currentPlayer, chooseNum(), *board);
            runTurn();                
            break; 

        case 4:
            DevelopmentCard::buyDevelopmentCard(currentPlayer);
            runTurn();                
            break; 

        case 5:
            tradeResources();
            runTurn();                
            break; 

        case 6:
            tradeDevelopmentCard();
            runTurn();
            break; 

        case 7:
            DevelopmentCard::useDevelopmentCard(currentPlayer, *board, this);
            runTurn();
            break; 

        case 8:
            board->printTiles();
            runTurn();
            break;

        case 9:
            board->printPathsOwners();
            runTurn();                
            break;

        case 10:
            board->printNodesOwners();
            runTurn();
            break;

        case 11:
            p = &choosePlayer();
            p->printCards();
            cout << p->getCardsCounter() << endl;
            runTurn();                
            break; 

        case 12:
            currentPlayer.get().printDevelopmentCards();
            runTurn();
            break;

        case 13:
            nextTurn();
            runTurn(true);
            break;

        case 14:
            endGame();                
            break;

        default:
            cout << "Invalid choice, try again" << endl;
            runTurn();
        }
    } else {
        endGame();                
    }
}

int Catan::rollDice() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, 6);

    int dice1 = distribution(generator);
    int dice2 = distribution(generator);
    int diceNum = dice1 + dice2;

    cout << "The number " << diceNum << " came out of the dice" << endl;
    if (diceNum == 7) {
        for (Player& p : players) {
            if (p.getCardsCounter() > 7) {
                cout << p.getName() << ", Unfortunately, you have to take down half of your cards" << endl;
                p.printCards();
                p.reduceCards();
            }
        }
    } else {
        for (Player& p : players) {
            p.getCards(diceNum);
        }
    }
    return diceNum;
}

unsigned int Catan::chooseNum(){
    unsigned int num;
    while (true) { 
        try {    
            if (!(cin >> num)) {
                throw invalid_argument("Invalid input, please enter a number.");
            }
            return num;
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

Player& Catan::choosePlayer() {
    unsigned int choice = 0;  // Use unsigned int for consistency with players.size()
    
    while (true) {
        try {
            cout << "Choose a player by number:" << endl;
            for (size_t i = 0; i < players.size(); ++i) {
                cout << i + 1 << " - " << players[i].get().getName() << endl;
            }
            
            if (!(cin >> choice) || choice < 1 || choice > players.size()) {
                throw invalid_argument("Invalid choice, please select a valid player number.");
            }
            
            return players[choice - 1].get();  // choice is now unsigned, matching players.size()
        } catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Catan::tradeResources() {
    for(Player& p: players){
        p.printCards();
    }

    string bring;
    string get;
    Player& p = choosePlayer();

    cout << p.getName() << " do you agree to trade? 0 - No, 1 - Yes" << endl;
    if (agreeToTrade(p.getName())){
        cout << "Which resource card would you like to bring? wood, bricks, wheat, ore, wool" << endl;
        cin >> bring;
        cout << "How many cards? ";
        unsigned int bringAmount = chooseNum();
        cout << "Which resource card would you like to get? wood, bricks, wheat, ore, wool" << endl;
        cin >> get;
        cout << "How many cards? ";
        unsigned int getAmount = chooseNum();
        cout << p.getName() << " do you agree to the trade? 0 - No, 1 - Yes" << endl;
        if (agreeToTrade(p.getName())){
            currentPlayer.get().trade(p, bring, get, bringAmount, getAmount);
        }
    }
}

bool Catan::agreeToTrade(string playerName){
    string agree;
    cin >> agree;
    if (agree == "1"){return true;}
    if(agree == "0"){
        cout << playerName << " do not agree to the trade." << endl;
        return false;}
    else{
        cout << "Invalid input, try again" << endl;
        return agreeToTrade(playerName);
    }
}

void Catan::tradeDevelopmentCard() {
    Player& p = choosePlayer();
    cout << p.getName() << " do you agree to trade? 0 - No, 1 - Yes" << endl;

    if (agreeToDevelopmentTrade(p.getName())){
        p.printDevelopmentCards();
        cout << "Which development card would you like to give? 1 - Monopol, 2 - Build2Roads, 3 - GetResources, 4 - Knight, 5 - VictoryPoint" << endl;
        unsigned int give = chooseNum();
        cout << "How many cards? ";
        unsigned int bringAmount = chooseNum();
        cout << "Which development card would you like to get? 1 - Monopol, 2 - Build2Roads, 3 - GetResources, 4 - Knight, 5 - VictoryPoint" << endl;
        unsigned int get = chooseNum();
        cout << "How many cards? ";
        unsigned int getAmount = chooseNum();

        cout << p.getName() << " do you agree to the trade? 0 - No, 1 - Yes" << endl;
        if (agreeToDevelopmentTrade(p.getName())){
            DevelopmentCardType giveType = DevelopmentCard::matchType(give);
            DevelopmentCardType getType = DevelopmentCard::matchType(get);
            DevelopmentCard::trade(currentPlayer, p, giveType, getType, bringAmount, getAmount);
        }
    }
}

bool Catan::agreeToDevelopmentTrade(string playerName){
    string agree;
    cin >> agree;
    if (agree == "1"){
        return true;
    }
    if(agree == "0"){
        cout << playerName << " do not agree the to trade" << endl;
        return false;}
    else{
        cout << "Invalid input, try again" << endl;
        return agreeToDevelopmentTrade(playerName);
    }
}

void Catan::nextTurn() {
    turn++;
    turn = turn % players.size();
    currentPlayer = players[turn];
}

void Catan::endGame() {
    cout << "This is the end of the game! These are the results:" << endl;
    for (Player& p : players) {
        cout << p.getName() << " Has: " << p.getPoints() << " points" << endl;
    }
    exit(0);
}
}

