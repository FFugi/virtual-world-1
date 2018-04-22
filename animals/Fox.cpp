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
        world.Log(FullName()+ " has no possible moves ", Color::YELLOW);
        return;
    }
    Position newPosition = positions.at(rand() % positions.size());
    Organism *neighbour = world.GetAtField(newPosition);
    if(neighbour != nullptr){
        neighbour->Collision(this, true);
        return;
    }
    world.MoveOrganism(this, newPosition);
}

Organism *Fox::GetNewOrganism() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Fox(newPosition, world);
}
