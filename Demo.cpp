/**
 * Demo file for Ex3.
 *
 */
#include <iostream>
#include <stdexcept>
#include <vector>
#include "Catan.hpp"
using namespace std;
using namespace ariel;

int main(){
    ariel::Player p1("Amit");
    ariel::Player p2("Yossi");
    ariel::Player p3("Dana");
    ariel::Catan game(p1, p2, p3);

}
