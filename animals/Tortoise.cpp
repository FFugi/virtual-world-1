//
// Created by ffugi on 04.04.18.
//

#include "Tortoise.hpp"

void Tortoise::Action() {
    if (rand() % 100 < 25) {
        Animal::Action();
    }
}

Organism *Tortoise::Procreate() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Tortoise(newPosition, world);
}

void Tortoise::Collision(Organism *other, bool isAttacked) {
    if (typeid(*this).name() == typeid(*other).name() ||
        other->GetStrength() >= 5) {
        Animal::Collision(other, isAttacked);

    } else {
        world.Log(FullName() + " resisted attack of " + other->FullName(),
                  Color::YELLOW);
    }
}