//
// Created by ffugi on 26.03.18.
//
#include <ncurses.h>
#include "World.hpp"


void World::AddOrganism(Organism *toAdd) {
    organisms.push_back(toAdd);
    wasOrganismAdded = true;
    // TODO sorting vector
}

void World::Render() {
    RenderFrame();
    logger.RenderFrame();
    for (auto org: organisms) {
        org->Display({position.x + 1, position.y + 1});
    }
    RenderLegend();
    RenderSignature();
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
    for (auto org:organisms) {
        delete org;
    }
    endwin();
}

void World::Log(std::string log) {
    logger.Log(std::move(log));
}

void World::Log(std::string log, int colorPair) {
    logger.Log(std::move(log), colorPair);
}

void World::NextTurn() {
    clear();
    logger.Reset();
    logger.Log("Turn number: " + std::to_string(numberOfTurn));
    if(wasOrganismAdded) {
        std::sort(organisms.begin(), organisms.end(),
                  Organism::CompareInitiative);
        wasOrganismAdded = false;
    }
    std::size_t iterations = organisms.size();
    for (std::size_t i = 0; i < iterations; i++) {
        if (organisms.at(i)->IsAlive()) {
            organisms.at(i)->Action();
        }
    }
    for(auto org : organisms){
        org->IncrementAge();
    }
    CleanDeadOrganisms();
    numberOfTurn++;
}

void World::CleanDeadOrganisms() {
    std::vector<Organism *> toDelete;
    for (std::size_t i = 0; i < organisms.size(); i++) {
        if (!organisms.at(i)->IsAlive()) {
            toDelete.push_back(organisms.at(i));
        }
    }
    organisms.erase(std::remove_if(organisms.begin(), organisms.end(),
                                   [](const Organism *org) {
                                       return !org->IsAlive();
                                   }), organisms.end());
    for (auto org : toDelete) {
        delete org;
    }
}

void World::RenderFrame() {
    for (int y = position.y + 1, real = 0; y <= position.y + height; real++,
            y++) {
        move(y, position.x - 1);
        addch(std::to_string(real % 10).at(0));
        if (real % 10 == 0) {
            move(y, position.x -2);
            addch(std::to_string(real % 100).at(0));
        }
        move(y, position.x);
        addch('|');
        move(y, position.x + width + 1);
        addch('|');
    }
    for (int x = position.x + 1, real = 0;
         x <= position.x + width; real++, x++) {
        if (real % 2 == 0) {
            move(position.y - 1, x);
            addch(std::to_string(real % 10).at(0));
        }
        if (real % 10 == 0) {
            move(position.y - 2, x);
            addch(std::to_string(real % 100).at(0));
        }
        move(position.y, x);
        addch('-');
        move(position.y + height + 1, x);
        addch('-');
    }
    move(position.y, position.x);
    addch('o');
    move(position.y, position.x + width + 1);
    addch('o');
    move(position.y + height + 1, position.x + width + 1);
    addch('o');
    move(position.y + height + 1, position.x);
    addch('o');
}

void World::RenderSignature() {
    int xSignature = position.x + width + 4;
    int ySignature = position.y - 2;
    move(ySignature, xSignature);
    addstr("Filip Fudala 171560");
}

void World::RenderLegend() {
    int xLegend = position.x + width + 4;
    int yLegend = position.y;
    move(yLegend++, xLegend);
    addstr("\t<=-Animals-=>");
    move(yLegend++, xLegend);
    addstr("S - Sheep\t (Owca)");
    move(yLegend++, xLegend);
    addstr("W - Wolf\t (Wilk)");
    move(yLegend++, xLegend);
    addstr("A - Antelope\t (Antylopa)");
    move(yLegend++, xLegend);
    addstr("F - Fox\t (Lis)");
    move(yLegend++, xLegend);
    addstr("T - Turtle\t (Zolw)");
    move(yLegend++, xLegend);
    addstr("S - Sheep\t (Owca)");
    move(yLegend++, xLegend);
    move(yLegend++, xLegend);
    addstr("\t<=-Plants-=>");
    move(yLegend++, xLegend);
    addstr("h - Hogweed\t (Barszcz Sosnowskiego)");
    move(yLegend++, xLegend);
    addstr("g - Grass\t (Trawa)");
    move(yLegend++, xLegend);
    addstr("s - Sonchus\t (Mlecz)");
    move(yLegend++, xLegend);
    addstr("G - Guarana\t (Guarana)");
    move(yLegend, xLegend);
    addstr("b - Wolf Berries\t (Wilcze Jagody)");
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
    // up-left
    if (pos.y != 0 && pos.x != 0) {
        possibleMoves.push_back({pos.x - 1, pos.y - 1});
    }
    // up-right
    if (pos.y != 0 && pos.x != width - 1) {
        possibleMoves.push_back({pos.x + 1, pos.y - 1});
    }
    // down-right
    if (pos.y != height - 1 && pos.x != width - 1) {
        possibleMoves.push_back({pos.x + 1, pos.y + 1});
    }
    // down-left
    if (pos.y != height - 1 && pos.x != 0) {
        possibleMoves.push_back({pos.x - 1, pos.y + 1});
    }
    return possibleMoves;
}
