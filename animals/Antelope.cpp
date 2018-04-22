//
// Created by ffugi on 06.04.18.
//

#include "Antelope.hpp"

void Antelope::Action() {
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
        Organism *newOrganism = GetNewOrganism();
        if (newOrganism == nullptr) {
            //  world.Log(name + " cannot procreate - no space!");
            return;
        }
        world.Log(FullName() + " and " + other->FullName() + " make:",
                  Color::GREEN);
        world.Log("New " + newOrganism->FullName(), Color::GREEN);
        world.AddOrganism(newOrganism);
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
            world.Log(FullName() + " runs away from " + other->FullName(),
                      Color::YELLOW);
            world.MoveOrganism(this, newPosition);
        }
        catch (World::NoPossibleFieldException &e) {
            world.Log(FullName() + " couldn't away from " + other->FullName(),
                      Color::YELLOW);
            Animal::Collision(other, isAttacked);
        }
    }
}
