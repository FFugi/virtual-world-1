#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "Grass.hpp"
#include <ctime>

int main() {
    srand(time(nullptr));

    World simulation(20, 10);
    bool continueSimulation = true;
    Sheep ofca({0,0}, simulation);
    Sheep ofca2({9,0}, simulation);
    Grass traffka({3,3}, simulation);
    simulation.AddOrganism(&ofca);
    simulation.AddOrganism(&ofca2);
    simulation.AddOrganism(&traffka);
    while(continueSimulation){
        simulation.Render();
        continueSimulation = simulation.NextTurn();
    }
    return 0;
}

