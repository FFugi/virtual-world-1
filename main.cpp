#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "Grass.hpp"
#include <ctime>

int main() {
    srand(time(nullptr));

    World simulation(30, 15);
    bool continueSimulation = true;
    Sheep ofca({0,0}, simulation);
    Sheep ofca2({12,0}, simulation);
    Grass traffka({3,3}, simulation);
    simulation.AddOrganism(&ofca);
    simulation.AddOrganism(&ofca2);
    simulation.AddOrganism(&traffka);
    while(continueSimulation){
        continueSimulation = simulation.NextTurn();
        simulation.Render();
    }
    return 0;
}

