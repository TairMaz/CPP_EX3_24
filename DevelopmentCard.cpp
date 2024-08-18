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
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 4);
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
    return player.cards.at("wheat") >= 1 && player.cards.at("wool") >= 1 && player.cards.at("ore") >= 1;
}

void DevelopmentCard::buyDevelopmentCard(Player& player) {
    if (canBuyDevelopmentCard(player)) {
        player.cards["wheat"]--;
        player.cards["wool"]--;
        player.cards["ore"]--;
        player.getCardsCounter() -= 3;

        DevelopmentCard newCard = pickCard();
        player.addDevelopmentCard(newCard);

        cout << "Bought a new development card!" << endl;
    } else {
        cout << "Not enough resources to buy a development card." << endl;
    }
}

void DevelopmentCard::useDevelopmentCard(Player& player, Board& board, Catan* game, bool ask, int cardNumber) {
    std::map<int, DevelopmentCardType> cardMap = {
        {1, DevelopmentCardType::Monopol},
        {2, DevelopmentCardType::Build2Roads},
        {3, DevelopmentCardType::GetResources}
    };
    if (ask==true){
        player.printDevelopmentCards();
        std::cout << "Which card would you like to use? (1 - Monopol, 2 - Build 2 Roads, 3 - Get Resources): ";
        std::cin >> cardNumber;
    }

    // המרת המספר שהוזן לסוג קלף הפיתוח
    auto itCardMap = cardMap.find(cardNumber);
    if (itCardMap == cardMap.end()) {
        std::cout << "Invalid card number." << std::endl;
        return;
    }

    DevelopmentCardType type = itCardMap->second;

    // חיפוש הקלף ברשימת הקלפים של השחקן
    auto it = std::find_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [type](DevelopmentCard& card) {
        return card.type == type;
    });

    if (it != player.getDevelopmentCards().end()) {
        switch (type) {
            case DevelopmentCardType::Monopol:
                Monopol(player, game, ask);
                player.deleteDevelopmentCard(it);
                break;
            case DevelopmentCardType::Build2Roads:
                Build2Roads(player, board, ask);
                player.deleteDevelopmentCard(it);
                break;
            case DevelopmentCardType::GetResources:
                GetResources(player);
                player.deleteDevelopmentCard(it);
                break;
            case DevelopmentCardType::Knight:
                std::cout << "There is no way to use a Knight card" << std::endl;
                break;
            case DevelopmentCardType::VictoryPoint:
                std::cout << "There is no way to use a VictoryPoint card" << std::endl;
                break;
        }
    } else {
        std::cout << "No such development card available." << std::endl;
    }
}

void DevelopmentCard::Monopol(Player& player, Catan* game, bool ask, std::string type) {
    if (ask==true){
        cout << "Which resource card would you like to take from everyone? ";
        cin >> type;}

    if(type != "wheat" && type != "ore" && type != "wool" && type != "wood" && type != "bricks") {
        cout << "Invalid choice, Try again" << endl;
        cin >> type;
    }

    for(Player& p : game->getPlayers()) {
        if(player.getName() != p.getName() && p.cards[type] > 0) {
            player.cards[type] += p.cards[type];
            p.getCardsCounter() -= p.cards[type];
            player.getCardsCounter() += p.cards[type];
            p.cards[type] = 0;
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

    player.cards[type1]++;
    player.cards[type2]++;
    player.getCardsCounter() += 2;
    cout << "Using Get Resources card." << endl;
}

void DevelopmentCard::trade(Player& player, Player& other, DevelopmentCardType bring, DevelopmentCardType get, unsigned int bringAmount, unsigned int getAmount) {
    auto getCount = [&] (const Player& player, DevelopmentCardType type) -> unsigned int {
        return std::count_if(player.getDevelopmentCards().begin(), player.getDevelopmentCards().end(), [type](const DevelopmentCard& card) {
            return card.getType() == type;
        });
    };

    if (getCount(other, get) < bringAmount || getCount(player, bring) < getAmount) {
        cout << "The trade is not possible" << endl;
        return;
    }

auto tradeCards = [] (Player& from, Player& to, DevelopmentCardType type, unsigned int amount) {
    unsigned int count = 0;
    auto& cards = from.getDevelopmentCards();
    int initialKnights = from.getKnights(); // שמירת מספר האבירים ההתחלתי
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

    if (type == DevelopmentCardType::Knight && initialKnights >= 3 && from.getKnights() < 3) {
        from.getPoints() -= 2;
    }
};


    tradeCards(other, player, get, getAmount);
    tradeCards(player, other, bring, bringAmount);

    cout << "The trade was completed successfully!" << endl;
}


string DevelopmentCard::TypeToString(DevelopmentCardType type) {
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

} // namespace ariel
