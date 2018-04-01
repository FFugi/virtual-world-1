//
// Created by ffugi on 26.03.18.
//
#include <ncurses.h>
#include "World.hpp"

World::World(): width(20), height(20) {

}

World::World(int width, int height): width(width), height(height){
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    refresh();
}

void World::AddOrganism(Organism *toAdd) {
    organisms.push_back(toAdd);
    // TODO sorting vector
}

void World::Render() {
    clear();
    for (auto org: organisms){
        org->Display();
    }
    refresh();
}

World::~World() {
    endwin();
}

bool World::NextTurn() {
    for (auto org: organisms){
        org->Action();
    }
    char sign = getch();
    numberOfTurn++;
    return sign != 'q';
}

std::vector<Position> World::GetPossibleFields(Position pos) {
    std::vector<Position> possibleMoves;
    if(pos.x != 0){
        possibleMoves.push_back({pos.x - 1, pos.y});
    }
    if(pos.x != width - 1){
        possibleMoves.push_back({pos.x + 1, pos.y});
    }
    if(pos.y != 0){
        possibleMoves.push_back({pos.x, pos.y - 1});
    }
    if(pos.y != height - 1){
        possibleMoves.push_back({pos.x, pos.y + 1});
    }
    return possibleMoves;
}
