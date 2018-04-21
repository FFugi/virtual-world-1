//
// Created by ffugi on 04.04.18.
//

#include "Turtle.hpp"

void Turtle::Action() {
    if (rand() % 100 < 25) {
        Animal::Action();
    }
}

Organism *Turtle::Procreate() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Turtle(newPosition, world);
}

void Turtle::Collision(Organism *other, bool isAttacked) {
    if (typeid(*this).name() == typeid(*other).name() ||
        other->GetStrength() >= 5) {
        Animal::Collision(other, isAttacked);
    }
    world.Log(FullName() + " resisted attack of " + other->FullName(),
              Color::YELLOW);
}