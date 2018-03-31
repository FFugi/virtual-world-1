#include <iostream>
#include <ncurses.h>
#include "World.hpp"

int main() {
    World simulation(10, 20);
    bool continueSimulation = true;
    while(continueSimulation){
        continueSimulation = simulation.NextTurn();
    }
    return 0;
}

