// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#include "DevelopmentCard.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Build.hpp"
#include "Catan.hpp"
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;

namespace ariel {

DevelopmentCard::DevelopmentCard(DevelopmentCardType t) : type(t) {}

DevelopmentCardType DevelopmentCard::getType() const {
    return type;
}

DevelopmentCard DevelopmentCard::pickCard() {
    // Picking a card at random:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, 4);
    int cardType = distribution(generator);

    switch (cardType) {
        case 0: return DevelopmentCard(DevelopmentCardType::Monopol);
        case 1: return DevelopmentCard(DevelopmentCardType::Build2Roads);
        case 2: return DevelopmentCard(DevelopmentCardType::GetResources);
        case 3: return DevelopmentCard(DevelopmentCardType::Knight);
        case 4: return DevelopmentCard(DevelopmentCardType::VictoryPoint);
        default: return DevelopmentCard(DevelopmentCardType::VictoryPoint);
    }
}

bool DevelopmentCard::canBuyDevelopmentCard(const Player& player) {
    return player.getCards().at("wheat") >= 1 && player.getCards().at("wool") >= 1 && player.getCards().at("ore") >= 1;
}

void DevelopmentCard::buyDevelopmentCard(Player& player) {
    if (canBuyDevelopmentCard(player)) {
        //The buy cards are removed if the player can buy development card
        player.getCards()["wheat"]--;
        player.getCards()["wool"]--;
        player.getCards()["ore"]--;
        player.getCardsCounter() -= 3;

        DevelopmentCard newCard = pickCard();
        player.addDevelopmentCard(newCard);

        cout << "Bought a new development card!" << endl;
    } else {
        cout << "Not enough resources to buy a development card." << endl;
    }
}

void DevelopmentCard::useDevelopmentCard(Player& player, Board& board, Catan* game, bool ask, int cardNumber) {
    map<int, DevelopmentCardType> cardMap = {
        {1, DevelopmentCardType::Monopol},
        {2, DevelopmentCardType::Build2Roads},
        {3, DevelopmentCardType::GetResources}
    };
    if (ask==true){
        player.printDevelopmentCards();
        cout << "Which card would you like to use? (1 - Monopol, 2 - Build 2 Roads, 3 - Get Resources): ";
        cin >> cardNumber;
    }

    // Convert the entered number to the development card type
    auto itCardMap = cardMap.find(cardNumber);
    if (itCardMap == cardMap.end()) {
        cout << "Invalid card number." << endl;
        return;
    }

    DevelopmentCardType type = itCardMap->second;

    // Search for the card in the player's card list
    auto it = find_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [type](DevelopmentCard& card) {
        return card.type == type;
    });

    // Performing the appropriate action according to the card the player has chosen
    if (it != player.getDevelopmentCards().end()) {
        switch (type) {
            case DevelopmentCardType::Monopol:
                Monopol(player, game, ask);
                player.getDevelopmentCards().erase(it);
                break;
            case DevelopmentCardType::Build2Roads:
                Build2Roads(player, board, ask);
                player.getDevelopmentCards().erase(it);
                break;
            case DevelopmentCardType::GetResources:
                GetResources(player);
                player.getDevelopmentCards().erase(it);
                break;
            case DevelopmentCardType::Knight:
                cout << "There is no way to use a Knight card" << endl;
                break;
            case DevelopmentCardType::VictoryPoint:
                cout << "There is no way to use a VictoryPoint card" << endl;
                break;
        }
    } else {
        cout << "No such development card available." << endl;
    }
}

void DevelopmentCard::Monopol(Player& player, Catan* game, bool ask, string type) {
    if (ask==true){
        cout << "Which resource card would you like to take from everyone? ";
        cin >> type;}

    if(type != "wheat" && type != "ore" && type != "wool" && type != "wood" && type != "bricks") {
        cout << "Invalid choice, Try again" << endl;
        cin >> type;
    }

    for(Player& p : game->getPlayers()) {
        // Taking the selected resource cards from the other players
        if(player.getName() != p.getName() && p.getCards()[type] > 0) {
            player.getCards()[type] += p.getCards()[type];
            p.getCardsCounter() -= p.getCards()[type];
            player.getCardsCounter() += p.getCards()[type];
            p.getCards()[type] = 0;
        }
    }
    cout << "Using Monopol card." << endl;
}

void DevelopmentCard::Build2Roads(Player& player, Board& board, bool ask, unsigned int place1, unsigned int place2) {
    if(ask==true){
        cout << "Where would you like to place the first road? ";
        cin >> place1;}
    Build::haveToPlaceRoad(player, place1, board);

    if(ask==true){
        cout << "Where would you like to place the second road? ";
        cin >> place2;}
    Build::haveToPlaceRoad(player, place2, board);

    cout << "Using Build 2 Roads card." << endl;
}

void DevelopmentCard::GetResources(Player& player) {
    string type1, type2;
    cout << "Which resource cards would you like to get? ";
    cin >> type1 >> type2;

    player.printCards();
    
    if((type1 != "wheat" && type1 != "ore" && type1 != "wool" && type1 != "wood" && type1 != "bricks") ||
       (type2 != "wheat" && type2 != "ore" && type2 != "wool" && type2 != "wood" && type2 != "bricks")) {
        cout << "Invalid choice, Try again" << endl;
        cin >> type1 >> type2;
    }

    // when the choice is valid the player receives the cards
    player.getCards()[type1]++;
    player.getCards()[type2]++;
    player.getCardsCounter() += 2;
    cout << "Using Get Resources card." << endl;
}

void DevelopmentCard::trade(Player& player, Player& other, DevelopmentCardType bring, DevelopmentCardType get, unsigned int bringAmount, unsigned int getAmount) {
    // Counts how many cards of a certain type a player has
    auto getCount = [&] (const Player& player, DevelopmentCardType type) -> unsigned int {
        return count_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [type](const DevelopmentCard& card) {
            return card.getType() == type;
        });
    };

    if (getCount(other, get) < getAmount || getCount(player, bring) < bringAmount) {
        cout << "The trade is not possible" << endl;
        return;
    }

// Makes a one-sided swap
auto tradeCards = [] (Player& from, Player& to, DevelopmentCardType type, unsigned int amount) {
    unsigned int count = 0;
    auto& cards = from.getDevelopmentCards();
    int initialKnights = from.getKnights(); // Keeping the starting number of knights
    for (auto it = cards.begin(); it != cards.end() && count < amount;) {
        if (it->getType() == type) {
            to.addDevelopmentCard(*it);
            it = cards.erase(it); 
            ++count;
            if (type == DevelopmentCardType::Knight){
                from.getKnights() -= 1;
            }
            if (type == DevelopmentCardType::VictoryPoint){
                from.getPoints() -= 1;
            }
        } else {
            ++it;
        }
    }

    //If the number of knights was greater than 3 and after the trade becomes less than 3, we will reduce 2 points for the player
    if (type == DevelopmentCardType::Knight && initialKnights >= 3 && from.getKnights() < 3) {
        from.getPoints() -= 2;
    }
};


    tradeCards(other, player, get, getAmount);
    tradeCards(player, other, bring, bringAmount);

    cout << "The trade was completed successfully!" << endl;
}


string DevelopmentCard::TypeToString(DevelopmentCardType type) {
    // Convert a card type to a string
    switch (type) {
        case DevelopmentCardType::Monopol: return "Monopol";
        case DevelopmentCardType::Build2Roads: return "Build 2 Roads";
        case DevelopmentCardType::GetResources: return "Get Resources";
        case DevelopmentCardType::Knight: return "Knight";
        case DevelopmentCardType::VictoryPoint: return "Victory Point";
        default: return "Unknown";
    }
}

DevelopmentCardType DevelopmentCard::matchType(unsigned int cardType) {
    // Matching a number to the type of card
    switch (cardType) {
        case 1: return DevelopmentCardType::Monopol;
        case 2: return DevelopmentCardType::Build2Roads;
        case 3: return DevelopmentCardType::GetResources;
        case 4: return DevelopmentCardType::Knight;
        case 5: return DevelopmentCardType::VictoryPoint;
        default:
            cout << "Try again, invalid choice.";
            cin >> cardType;
            return matchType(cardType);
    }
}

} 
