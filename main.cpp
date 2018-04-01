#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include <ctime>

int main() {
    srand(time(nullptr));

    World simulation(10, 20);
    bool continueSimulation = true;
    Sheep ofca({2,3}, simulation);
    simulation.AddOrganism(&ofca);
    while(continueSimulation){
        simulation.Render();
        continueSimulation = simulation.NextTurn();
    }
    return 0;
}

