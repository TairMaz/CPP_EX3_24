#include "Player.hpp"
#include <iostream>

namespace ariel {

Player::Player(std::string name) : name(name), cardsCounter(0), points(0), knights(0) {}

std::string Player::getName() const {
    return this->name;
}

std::vector<unsigned int>& Player::getRoads() {
    return this->roads;
}

std::map<unsigned int, std::string>& Player::getProperty() {
    return this->property;
}

void Player::setAccept(int at, std::string value) {
    accept[at].push_back(value);
}

std::vector<DevelopmentCard>& Player::getDevelopmentCards() {
    return developmentCards;
}

const std::vector<DevelopmentCard>& Player::getDevelopmentCards() const {
    return developmentCards;
}

void Player::deleteDevelopmentCard(std::vector<DevelopmentCard>::iterator it) {
    developmentCards.erase(it);
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
    std::cout << "Player " << name << " Cards:" << std::endl;
    for (const auto& pair : cards) {
        std::cout << "Resource: " << pair.first << ", Amount: " << pair.second << std::endl;
    }
}

void Player::printDevelopmentCards() const {
    std::map<DevelopmentCardType, int> cardCount;
    for (const auto& card : developmentCards) {
        cardCount[card.getType()]++; 
        
    }

    std::cout << "Player " << name << " development cards:" << std::endl;
    for (const auto& entry : cardCount) {
        std::cout << "- " << DevelopmentCard::TypeToString(entry.first) << ": " << entry.second << std::endl;
    }
}

void Player::reduceCards() {
    unsigned int wood, bricks, wheat, ore, wool;
    std::cout << "How much 'wood' would you like to take down? A number between 0 to your wood amount: ";
    std::cin >> wood;
    std::cout << "How much 'bricks'? ";
    std::cin >> bricks;
    std::cout << "'wheat'? ";
    std::cin >> wheat;
    std::cout << "'ore'? ";
    std::cin >> ore;
    std::cout << "'wool'? ";
    std::cin >> wool;

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
        std::cout << "Great, the taking down of the cards is complete" << std::endl;
    } else {
        std::cout << "The taking down of the cards is not good, try again" << std::endl;
        reduceCards(); 
        
    }
}

void Player::getCards(int diceNum) {
    for (const auto& str : accept[diceNum]) {
        cards[str]++;
        cardsCounter++;
    }
}

void Player::addCard(std::string resource, unsigned int amount){
    if(resource == "wheat" || resource == "wool" || resource == "wood" || resource == "ore" || resource == "bricks"){
    this->cards[resource] += amount;
    this->cardsCounter += amount; }
}

void Player::trade(Player& p, std::string bring, std::string get, unsigned int bringAmount, unsigned int getAmount) {
    if (p.getName()==name){
        std::cout << "The trade is not possible, you have chosen yourself." << std::endl;
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

            std::cout << "The trade was completed successfully!" << std::endl;
        } else {
            std::cout << "The trade is not possible" << std::endl;
        }
    }
}

} // namespace ariel
