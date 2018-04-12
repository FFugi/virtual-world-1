#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "plants/Grass.hpp"
#include "animals/Wolf.hpp"
#include "plants/Sonchus.hpp"
#include "animals/Fox.hpp"
#include "animals/Turtle.hpp"
#include "plants/Guarana.hpp"
#include "plants/WolfBerry.hpp"
#include "plants/Hogweed.hpp"
#include "animals/Sheep.hpp"
#include "animals/Antelope.hpp"
#include "serialization/Serializator.hpp"
#include <ctime>

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    refresh();
    // TODO colors with organisms
    init_pair(Logger::GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(Logger::RED, COLOR_RED, COLOR_BLACK);
    init_pair(Logger::YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(Logger::MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(Logger::CYAN, COLOR_CYAN, COLOR_BLACK);
    srand(time(nullptr));

    World simulation(60, 20);

    simulation.AddOrganism(new Fox({1,10},simulation));
    simulation.AddOrganism(new Fox({40,13},simulation));


    simulation.AddOrganism(new Sheep({10,10},simulation));
    simulation.AddOrganism(new Sheep({40,10},simulation));

    simulation.AddOrganism(new Turtle({0,14},simulation));
    simulation.AddOrganism(new Antelope({50,10},simulation));
    simulation.AddOrganism(new Wolf({51,10},simulation));

    simulation.AddOrganism(new Grass({0,0},simulation));
    simulation.AddOrganism(new Grass({59,14},simulation));
    simulation.AddOrganism(new Grass({0,14},simulation));
    simulation.AddOrganism(new Sonchus({59,0},simulation));
    simulation.AddOrganism(new Guarana({30,7},simulation));
    simulation.AddOrganism(new WolfBerry({29,7},simulation));
    simulation.AddOrganism(new Hogweed({5,7},simulation));
    simulation.Render();

    World::Command command;
    do{
        command = simulation.NextTurn();
        simulation.Render();
    }while(command != World::EXIT);
    return 0;
}

