// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#include "Player.hpp"
#include <iostream>

namespace ariel {

Player::Player(string name) : name(name), cardsCounter(0), points(0), knights(0) {}

string Player::getName() const {
    return this->name;
}

vector<unsigned int>& Player::getRoads() {
    return this->roads;
}

map<unsigned int, string>& Player::getProperty() {
    return this->property;
}

void Player::setAccept(int at, string value) {
    accept[at].push_back(value);
}

const map<string, unsigned int>& Player::getCards() const {
    return cards;
}

map<string, unsigned int>& Player::getCards() {
    return cards;
}

vector<DevelopmentCard>& Player::getDevelopmentCards() {
    return developmentCards;
}

const vector<DevelopmentCard>& Player::getDevelopmentCards() const {
    return developmentCards;
}

unsigned int& Player::getCardsCounter(){
    return this->cardsCounter;
}

void Player::addDevelopmentCard(DevelopmentCard& newCard) {
    developmentCards.push_back(newCard);
    if (newCard.getType() == DevelopmentCardType::VictoryPoint) {
        getPoints() += 1;
    } else if (newCard.getType() == DevelopmentCardType::Knight) {
        if (getKnights() == 2) {
            getPoints() += 2;
        }
        getKnights() += 1;
    }
}

int& Player::getPoints(){
    return points;
}

int& Player::getKnights(){  
    return this->knights;
}

void Player::printCards() const {
    cout << "Player " << name << " Cards:" << endl;
    for (const auto& pair : cards) {
        cout << "Resource: " << pair.first << ", Amount: " << pair.second << endl;
    }
}

void Player::printDevelopmentCards() const {
    map<DevelopmentCardType, int> cardCount;
    for (const auto& card : developmentCards) {
        cardCount[card.getType()]++; 
        
    }

    cout << "Player " << name << " development cards:" << endl;
    for (const auto& entry : cardCount) {
        cout << "- " << DevelopmentCard::TypeToString(entry.first) << ": " << entry.second << endl;
    }
}

void Player::reduceCards() {
    unsigned int wood, bricks, wheat, ore, wool;
    cout << "How much 'wood' would you like to take down? A number between 0 to your wood amount: ";
    cin >> wood;
    cout << "How much 'bricks'? ";
    cin >> bricks;
    cout << "'wheat'? ";
    cin >> wheat;
    cout << "'ore'? ";
    cin >> ore;
    cout << "'wool'? ";
    cin >> wool;

    if (((wood + bricks + wheat + ore + wool) == (cardsCounter/2)) &&
        (wood >= 0 && wood <= cards["wood"]) &&
        (bricks >= 0 && bricks <= cards["bricks"]) &&
        (wheat >= 0 && wheat <= cards["wheat"]) &&
        (ore >= 0 && ore <= cards["ore"]) &&
        (wool >= 0 && wool <= cards["wool"])) {
        cards["wood"] -= wood;
        cards["bricks"] -= bricks;
        cards["wheat"] -= wheat;
        cards["ore"] -= ore;
        cards["wool"] -= wool;
        cardsCounter -= (wood + bricks + wheat + ore + wool);
        cout << "Great, the taking down of the cards is complete" << endl;
    } else {
        cout << "The taking down of the cards is not good, try again" << endl;
        reduceCards(); 
        
    }
}

void Player::getCards(int diceNum) {
    for (const auto& str : accept[diceNum]) {
        cards[str]++;
        cardsCounter++;
    }
}

void Player::addCard(string resource, unsigned int amount){
    if(resource == "wheat" || resource == "wool" || resource == "wood" || resource == "ore" || resource == "bricks"){
    this->cards[resource] += amount;
    this->cardsCounter += amount; }
}

void Player::trade(Player& p, string bring, string get, unsigned int bringAmount, unsigned int getAmount) {
    if (p.getName()==name){
        cout << "The trade is not possible, you have chosen yourself." << endl;
    }
    else{
        if ((get == "wood" || get == "bricks" || get == "wheat" || get == "ore" || get == "wool") &&
            (bring == "wood" || bring == "bricks" || bring == "wheat" || bring == "ore" || bring == "wool") &&
            (this->cards[bring] >= bringAmount) &&
            p.cards[get] >= getAmount) {
            this->cards[bring] -= bringAmount;
            this->cards[get] += getAmount;
            cardsCounter = cardsCounter + getAmount - bringAmount;
            p.cards[bring] += bringAmount;
            p.cards[get] -= getAmount;
            p.getCardsCounter() += bringAmount;
            p.getCardsCounter() -= getAmount;

            cout << "The trade was completed successfully!" << endl;
        } else {
            cout << "The trade is not possible" << endl;
        }
    }
}

} 
