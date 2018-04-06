#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "plants/Grass.hpp"
#include "animals/Wolf.hpp"
#include "plants/Sonchus.hpp"
#include "animals/Fox.hpp"
#include "animals/Turtle.hpp"
#include "plants/Guarana.hpp"
#include "WolfBerry.hpp"
#include "Hogweed.hpp"
#include "animals/Sheep.hpp"
#include <ctime>

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    refresh();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    srand(time(nullptr));

    World simulation(60, 15);
    bool continueSimulation = true;
    simulation.AddOrganism(new Fox({1,10},simulation));

    simulation.AddOrganism(new Wolf({4,1},simulation));

    simulation.AddOrganism(new Sheep({10,10},simulation));
    simulation.AddOrganism(new Sheep({20,10},simulation));

    simulation.AddOrganism(new Fox({0,13},simulation));
    simulation.AddOrganism(new Turtle({0,14},simulation));

    simulation.AddOrganism(new Grass({0,0},simulation));
    simulation.AddOrganism(new Grass({59,14},simulation));
    simulation.AddOrganism(new Grass({0,14},simulation));
    simulation.AddOrganism(new Sonchus({59,0},simulation));
    simulation.AddOrganism(new Guarana({30,7},simulation));
    simulation.AddOrganism(new WolfBerry({29,7},simulation));
    simulation.AddOrganism(new Hogweed({15,7},simulation));
    simulation.Render();
    while(continueSimulation){
        continueSimulation = getch() != 'q';
        simulation.NextTurn();
        simulation.Render();
    }
    return 0;
}

