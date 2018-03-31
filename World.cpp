//
// Created by ffugi on 26.03.18.
//
#include <ncurses.h>
#include "World.hpp"

World::World(): width(20), lenght(20) {

}

World::World(int width, int length): width(width), lenght(length) {
    initscr();
    printw("Welcome");
    refresh();
}

World::~World() {
    endwin();
}

bool World::NextTurn() {
    getch();
    return false;
}
