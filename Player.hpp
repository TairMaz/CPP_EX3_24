#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include "DevelopmentCard.hpp"

namespace ariel {

    class Player {
    private:
        std::string name;
        std::vector<unsigned int> roads;
        std::map<unsigned int, std::string> property;
        std::map<int, std::vector<std::string>> accept;
        std::vector<DevelopmentCard> developmentCards;
        unsigned int cardsCounter;
        int points;
        int knights;

    public:
        std::map<std::string, unsigned int> cards; 
        Player(std::string name);
        std::string getName() const;
        std::vector<unsigned int>& getRoads();
        std::map<unsigned int, std::string>& getProperty();
        void setAccept(int at, std::string value);
        std::vector<DevelopmentCard>& getDevelopmentCards();
        const std::vector<DevelopmentCard>& getDevelopmentCards() const;
        void deleteDevelopmentCard(std::vector<DevelopmentCard>::iterator it);
        unsigned int& getCardsCounter();
        void addDevelopmentCard(DevelopmentCard& newCard);
        int& getPoints();
        int& getKnights(); 
        void printCards() const;
        void printDevelopmentCards() const;
        void endTurn();
        void reduceCards();
        void getCards(int diceNum);
        void addCard(std::string resource, unsigned int amount);
        void trade(Player& p, std::string bring, std::string get, unsigned int bringAmount, unsigned int getAmount);
    };
}

#endif // PLAYER_HPP
