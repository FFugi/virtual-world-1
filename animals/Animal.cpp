//
// Created by ffugi on 01.04.18.
//

#include "Animal.hpp"
#include "../plants/Plant.hpp"



void Animal::Collision(Organism *other, bool isAttacked) {
    if (typeid(*this).name() == typeid(*other).name()) {
        // same animals, procreation!
        Procreate(other);
        return;
    }
    Fight(other);
}

void Animal::Action() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return;
    }
//    world.Log(FullName() + " moves to (" + std::to_string(newPosition.x) + ","
//              + std::to_string(newPosition.y) + ")");
    Organism *neighbour = world.GetAtField(newPosition);
    if (neighbour != nullptr) {
        neighbour->Collision(this, true);
        return;
    }
    world.MoveOrganism(this, newPosition);
}

void Animal::Fight(Organism *attacker) {
    // fight
    if (attacker->GetStrength() >= strength) {
        Kill(attacker);
        world.MoveOrganism(attacker, position);
    } else {
        attacker->Kill(this);
    }

}

void Animal::Procreate(Organism *other) {
    Organism *newOrganism = GetNewOrganism();
    if (newOrganism == nullptr) {
        //  world.Log(name + " cannot procreate - no space!");
        return;
    }
    world.Log(FullName() + " and " + other->FullName() + " make:",
              Color::GREEN);
    world.Log("New " + newOrganism->FullName(), Color::GREEN);
    world.AddOrganism(newOrganism);
}

