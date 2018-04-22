//
// Created by ffugi on 06.04.18.
//

#include "Antelope.hpp"

void Antelope::Action() {
    //TODO fix
    Animal::Action();
    Animal::Action();
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
