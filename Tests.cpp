#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Catan.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "DevelopmentCard.hpp"
#include "Build.hpp"
#include <sstream>
#include <iostream>

using namespace ariel;

TEST_CASE("Player tests") {

    // Create players
    ariel::Player player1("Alice");
    ariel::Player player2("Bob");

    // check names
    CHECK(player1.getName() == "Alice");
    CHECK(player2.getName() == "Bob");

    // Check points
    player1.getPoints() += 3;
    player2.getPoints() += 5;
    CHECK(player1.getPoints() == 3);
    CHECK(player2.getPoints() == 5);

    player1.getPoints() -= 1;
    CHECK(player1.getPoints() == 2);

    player2.getKnights() += 2;
    CHECK(player2.getKnights() == 2);
    cout << player2.getKnights();
}

TEST_CASE("Board tests") {
    ariel::Board board;

    // Check sizes of the vectors
    CHECK(board.getTiles().size() == 19);
    CHECK(board.getNodesOwners().size() == 54);
    CHECK(board.getPathsOwners().size() == 72);

}


TEST_CASE("Catan game tests") {
    ariel::Player p1("Amit");
    ariel::Player p2("Yossi");
    ariel::Player p3("Dana");
    ariel::Catan game(p1, p2, p3, false);

    CHECK(Build::placeRoad(game.getCurrentPlayer(), 52, game.getBoard()));
    CHECK(Build::placeSettelemnt(game.getCurrentPlayer(), 44, game.getBoard()));
    CHECK(Build::placeRoad(game.getCurrentPlayer(), 56, game.getBoard()));
    CHECK_FALSE(Build::placeSettelemnt(game.getCurrentPlayer(), 29, game.getBoard())); // There is no road lead this node
    CHECK(Build::placeSettelemnt(game.getCurrentPlayer(), 40, game.getBoard()));
    game.nextTurn();


    CHECK(Build::placeRoad(game.getCurrentPlayer(), 58, game.getBoard())); 
    CHECK_FALSE(Build::placeSettelemnt(game.getCurrentPlayer(), 43, game.getBoard())); // There is a Settelemnt in the adjacent node
    CHECK(Build::placeSettelemnt(game.getCurrentPlayer(), 42, game.getBoard()));
    CHECK(Build::placeRoad(game.getCurrentPlayer(), 21, game.getBoard())); 
    CHECK(Build::placeSettelemnt(game.getCurrentPlayer(), 13, game.getBoard()));
    game.nextTurn();

    CHECK(Build::placeRoad(game.getCurrentPlayer(), 13, game.getBoard())); 
    CHECK(Build::placeSettelemnt(game.getCurrentPlayer(), 10, game.getBoard()));
    CHECK_FALSE(Build::placeRoad(game.getCurrentPlayer(), 56, game.getBoard())); // Road already placed
    CHECK(Build::placeRoad(game.getCurrentPlayer(), 41, game.getBoard())); 
    CHECK(Build::placeSettelemnt(game.getCurrentPlayer(), 29, game.getBoard()));
    game.nextTurn();


    CHECK(p1.getRoads().size() == 2);
    CHECK(p2.getRoads().size() == 2);
    CHECK(p3.getRoads().size() == 2);

    CHECK(p1.getProperty().size() == 2);
    CHECK(p2.getProperty().size() == 2);
    CHECK(p3.getProperty().size() == 2);

    CHECK(p1.cards.size() == 3);

    //p1 make a trade and buy development card
    p1.trade(p2, "bricks", "wool", 1, 1);
    p1.trade(p3, "wood", "wheat", 1, 1);
    DevelopmentCard::buyDevelopmentCard(p1);
    CHECK(p1.getDevelopmentCards().size()==1);

    // p2 place road and settelemnt
    CHECK_FALSE(Build::placeRoad(p2, 8, game.getBoard())); 
    CHECK(Build::placeRoad(p2, 30, game.getBoard())); 
    CHECK_FALSE(Build::placeSettelemnt(p2, 24, game.getBoard())); // There is no neccesry resources

    // p3 place a city
    p3.addCard("wheat", 2);
    p3.addCard("ore", 3);
    CHECK_FALSE(Build::placeCity(p3, 13, game.getBoard())); // The player has no settlement at the chosen node
    CHECK(Build::placeCity(p3, 29, game.getBoard()));

    CHECK(p3.getPoints() == 3);
    CHECK(game.getCurrentPlayer().get().getName() == "Amit");

    int diceNum = game.rollDice();
    CHECK(diceNum >= 2);
    CHECK(diceNum <= 12);
}

TEST_CASE("Development Card") {
    ariel::Player p1("Amit");
    ariel::Player p2("Yossi");
    ariel::Player p3("Dana");
    ariel::Catan game(p1, p2, p3, false);

    CHECK(p1.getCardsCounter()==0);
    CHECK(p2.getCardsCounter()==0);
    CHECK(p3.getCardsCounter()==0);


    DevelopmentCard victoryPoint1(DevelopmentCardType::VictoryPoint);
    DevelopmentCard victoryPoint2(DevelopmentCardType::VictoryPoint);
    DevelopmentCard knight1(DevelopmentCardType::Knight);
    DevelopmentCard knight2(DevelopmentCardType::Knight);
    DevelopmentCard knight3(DevelopmentCardType::Knight);
    DevelopmentCard knight4(DevelopmentCardType::Knight);
    DevelopmentCard knight5(DevelopmentCardType::Knight);


    p1.addDevelopmentCard(victoryPoint1);
    p1.addDevelopmentCard(victoryPoint2);
    p1.addDevelopmentCard(knight1);
    p1.addDevelopmentCard(knight2);

    p2.addDevelopmentCard(knight3);
    p2.addDevelopmentCard(knight4);
    p2.addDevelopmentCard(knight5);

    CHECK(p1.getPoints() == 2);
    CHECK(p2.getPoints() == 2);

    DevelopmentCard::trade(p1, p2, DevelopmentCardType::VictoryPoint, DevelopmentCardType::Knight, 1, 1);

    CHECK(p1.getPoints() == 3);
    CHECK(p2.getPoints() == 1);


    DevelopmentCard monopol(DevelopmentCardType::Monopol);
    p3.addDevelopmentCard(monopol);
    p1.addCard("wheat", 10);
    p2.addCard("wheat", 5);
    DevelopmentCard::useDevelopmentCard(p3, game.getBoard(), &game, false);
    CHECK(p3.cards["wheat"]==15);
    CHECK(p2.getCardsCounter()==0);


    Build::placeRoad(p2, 52, game.getBoard());
    Build::placeSettelemnt(p2, 44, game.getBoard());
    Build::placeRoad(p2, 7, game.getBoard());
    Build::placeSettelemnt(p2, 10, game.getBoard());

    DevelopmentCard build2Roads(DevelopmentCardType::Build2Roads);
    p2.addDevelopmentCard(build2Roads);
    DevelopmentCard::useDevelopmentCard(p2, game.getBoard(), &game, false, 2);
    CHECK(p2.getRoads().size()==4);

}