#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "Grass.hpp"
#include "Wolf.hpp"
#include "Sonchus.hpp"
#include "Fox.hpp"
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
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    srand(time(nullptr));

    World simulation(60, 15);
    bool continueSimulation = true;
    simulation.AddOrganism(new Fox({1,1},simulation));

    simulation.AddOrganism(new Wolf({4,1},simulation));

    simulation.AddOrganism(new Sheep({10,10},simulation));
    simulation.AddOrganism(new Sheep({20,10},simulation));

    simulation.AddOrganism(new Grass({13,0},simulation));
    simulation.AddOrganism(new Sonchus({59,10},simulation));
    simulation.Render();
    while(continueSimulation){
        simulation.NextTurn();
        simulation.Render();
        continueSimulation = getch() != 'q';
    }
    return 0;
}

