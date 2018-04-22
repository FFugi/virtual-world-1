#include <iostream>
#include <ncurses.h>
#include "World.hpp"
#include "plants/Grass.hpp"
#include "animals/Wolf.hpp"
#include "plants/Sonchus.hpp"
#include "animals/Fox.hpp"
#include "animals/Tortoise.hpp"
#include "plants/Guarana.hpp"
#include "plants/WolfBerry.hpp"
#include "plants/Hogweed.hpp"
#include "animals/Sheep.hpp"
#include "animals/Antelope.hpp"
#include "serialization/Serializer.hpp"
#include "Color.hpp"
#include "animals/Human.hpp"
#include "Menu.hpp"
#include <ctime>

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    start_color();
    keypad(stdscr, true);
    refresh();
    init_pair(static_cast<int>(Color::GREEN), COLOR_GREEN, COLOR_BLACK);
    init_pair(static_cast<int>(Color::RED), COLOR_RED, COLOR_BLACK);
    init_pair(static_cast<int>(Color::YELLOW), COLOR_YELLOW, COLOR_BLACK);
    init_pair(static_cast<int>(Color::MAGENTA), COLOR_MAGENTA, COLOR_BLACK);
    init_pair(static_cast<int>(Color::CYAN), COLOR_CYAN, COLOR_BLACK);
    srand(time(nullptr));
    Menu menu;
    while(menu.Execute());

    return 0;
}

