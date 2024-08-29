// Tair Mazriv
// id: 209188382
// tairmazriv@gmail.com

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <map>
#include "DevelopmentCard.hpp"
using namespace std;

namespace ariel {

    class Player {
    private:
        string name;
        vector<unsigned int> roads;                 // the roads of the player according the places
        map<unsigned int, string> property;         // the cities and Settelemnt of each player
        map<int, vector<string>> accept;            // list of what resources the player gets for each number that comes out on the dice
        map<string, unsigned int> cards;            // the resources of the player and the amount
        vector<DevelopmentCard> developmentCards;   // the development cards
        unsigned int cardsCounter;                  // the amount of all the resources cards
        int points;
        int knights;


    public:
        Player(string name);
        string getName() const;
        vector<unsigned int>& getRoads();
        map<unsigned int, string>& getProperty();
        void setAccept(int at, string value);
        const std::map<std::string, unsigned int>& getCards() const;        
        std::map<std::string, unsigned int>& getCards();         
        vector<DevelopmentCard>& getDevelopmentCards();
        const vector<DevelopmentCard>& getDevelopmentCards() const;
        unsigned int& getCardsCounter();
        void addDevelopmentCard(DevelopmentCard& newCard);
        int& getPoints();
        int& getKnights(); 
        void printCards() const;
        void printDevelopmentCards() const;
        void reduceCards();          // if came 7 in dice, the player nead to choose ehich cards to take down
        void getCards(int diceNum);  // getting the cards according the dice number
        void addCard(string resource, unsigned int amount);
        void trade(Player& p, string bring, string get, unsigned int bringAmount, unsigned int getAmount);
    };
}

#endif 
