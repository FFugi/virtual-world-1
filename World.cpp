//
// Created by ffugi on 26.03.18.
//
#include <ncurses.h>
#include "World.hpp"

World::World() : width(20), height(20), numberOfTurn(0), logger({40, 2}) {

}

World::World(int width, int height) : width(width), height(height),
                                      numberOfTurn(0),
                                      logger({40, 2}) {
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
    RenderFrame();
    for (auto org: organisms) {
        org->Display(3, 3);
    }
    refresh();
}

// TODO remove n^2
Organism *World::GetAtField(Position pos) {
    for (auto org : organisms) {
        if (org->GetPosition() == pos) {
            return org;
        }
    }
    return nullptr;
}

World::~World() {
    endwin();
}

void World::Log(std::string log) {
    logger.Log(log);
}

bool World::NextTurn() {
    logger.Reset();
    logger.Log("Turn number: " + std::to_string(numberOfTurn));
    for (std::size_t i = 0; i < organisms.size(); i++) {
        organisms.at(i)->Action();
    }
    int sign = getch();
    numberOfTurn++;
    return sign != 'q';
}

void World::RenderFrame() {
    int begY = 2;
    int begX = 2;
    for (int y = begY + 1; y <= begY + height; y++) {
        move(y, begX);
        addch('|');
        move(y, begX + width + 1);
        addch('|');
    }
    for (int x = begX + 1; x <= begX + width; x++) {
        move(begY, x);
        addch('-');
        move(begY + height + 1, x);
        addch('-');
    }
}

Position World::GetRandomNeighbourFreeField(Position pos) {
    std::vector<Position> possibleMoves = GetNeighbourFields(pos);
    possibleMoves.erase(std::remove_if(possibleMoves.begin(), possibleMoves.end
            (), [&](const Position &pos) {
        return GetAtField(pos) != nullptr;
    }), possibleMoves.end());
    if (possibleMoves.size() == 0) {
        throw NoPossibleFieldException();
    }
    Position randomPos = possibleMoves.at(rand() % possibleMoves.size());
    return randomPos;
}

Position World::GetRandomNeighbourField(Position pos) {
    std::vector<Position> possibleMoves = GetNeighbourFields(pos);
    if (possibleMoves.size() == 0) {
        throw NoPossibleFieldException();
    }
    Position randomPos = possibleMoves.at(rand() % possibleMoves.size());
    return randomPos;
}

std::vector<Position> World::GetNeighbourFields(Position pos) {
    std::vector<Position> possibleMoves;
    if (pos.x != 0) {
        possibleMoves.push_back({pos.x - 1, pos.y});
    }
    if (pos.x != width - 1) {
        possibleMoves.push_back({pos.x + 1, pos.y});
    }
    if (pos.y != 0) {
        possibleMoves.push_back({pos.x, pos.y - 1});
    }
    if (pos.y != height - 1) {
        possibleMoves.push_back({pos.x, pos.y + 1});
    }
    return possibleMoves;
}
