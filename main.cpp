#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "Grass.hpp"
#include "Wolf.hpp"
#include <ctime>

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    refresh();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    srand(time(nullptr));

    World simulation(30, 15);
    bool continueSimulation = true;
    simulation.AddOrganism(new Sheep({0,0},simulation));
    simulation.AddOrganism(new Sheep({0,4},simulation));
    simulation.AddOrganism(new Wolf({5,4},simulation));
    simulation.AddOrganism(new Grass({13,0},simulation));
    simulation.Render();
    while(continueSimulation){
        simulation.NextTurn();
        simulation.Render();
        continueSimulation = getch() != 'q';
    }
    return 0;
}

