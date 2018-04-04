//
// Created by ffugi on 04.04.18.
//

#include "Fox.hpp"

void Fox::Action() {
    std::vector<Position> positions = world.GetNeighbourFields(position);
    positions.erase(std::remove_if(positions.begin(), positions.end(), [&]
            (Position pos) {
        Organism *org = world.GetAtField(pos);
        if (org == nullptr) {
            return false;
        }
        return org->GetStrength() > strength;
    }), positions.end());
    if (positions.size() == 0) {
        world.Log(FullName()+ " has no possible mocves ", 3);
        return;
    }
    Position newPosition = positions.at(rand() % positions.size());
    position = newPosition;
}

Organism *Fox::Procreate() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Sheep(newPosition, world);
}

void Fox::Display(Position beg) const {
    attron(COLOR_PAIR(2) | A_BOLD);
    Organism::Display(beg);
    attroff(COLOR_PAIR(2) | A_BOLD);
}
