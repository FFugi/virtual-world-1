//
// Created by ffugi on 06.04.18.
//

#include "Antelope.hpp"

void Antelope::Action() {
    for(std::size_t i = 0; i < 2; i++) {
        Position newPosition;
        try {
            newPosition = world.GetRandomNeighbourField(position);
        }
        catch (World::NoPossibleFieldException &e) {
            return;
        }
        Organism *neighbour = world.GetAtField(newPosition);
        if (neighbour != nullptr) {
            neighbour->Collision(this, true);
            return;
        }
        world.MoveOrganism(this, newPosition);
    }
}

Organism *Antelope::GetNewOrganism() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Antelope(newPosition, world);
}

void Antelope::Collision(Organism *other, bool isAttacked) {
    if (dynamic_cast<Antelope *>(other)) {
        Procreate(other);
        return;

    } else {
        bool willRunAway = rand() % 100 >= 50;
        if (!willRunAway) {
            Animal::Collision(other, isAttacked);
            return;
        }
        Position newPosition;
        try {
            newPosition = world.GetRandomNeighbourFreeField(position);
            world.Log(FullName() + " runs away from " + other->FullName()
                      + " to (" + std::to_string(newPosition.x) + "," +
                      std::to_string(newPosition.y) + ")", Color::YELLOW);
            world.MoveOrganism(other, position);
            world.MoveOrganism(this, newPosition);
        }
        catch (World::NoPossibleFieldException &e) {
            world.Log(FullName() + " couldn't away from " + other->FullName()
                      + " there was no place!",
                      Color::YELLOW);
            Animal::Collision(other, isAttacked);
        }
    }
}
