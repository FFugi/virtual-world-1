//
// Created by ffugi on 01.04.18.
//

#include "Animal.hpp"
#include "../plants/Plant.hpp"

Animal::Animal(Position position, World &world, int initiative, int strength,
               char symbol, std::string name) : Organism(position, world,
                                                         initiative,
                                                         strength,
                                                         symbol, name) {}


void Animal::Collision(Organism *other, bool isAttacked) {
    // TODO check plant?
    if (dynamic_cast<Plant *>(other)) {
        other->Collision(this, false);
        return;
    } else if (typeid(*this).name() == typeid(*other).name()) {
        // same animals, procreation!
        Organism *newOrganism = Procreate();
        if (newOrganism == nullptr) {
            //  world.Log(name + " cannot procreate - no space!");
            return;
        }
        world.Log(FullName() + " and " + other->FullName() + " make:",
                  Logger::GREEN);
        world.Log("New " + newOrganism->FullName(), Logger::GREEN);
        world.AddOrganism(newOrganism);
        return;
    }
    world.Log(other->FullName() + " attacks " + FullName());
    Fight(other);
}

void Animal::Action() {
    // TODO random move
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        // TODO log?
        return;
    }
//    world.Log(FullName() + " moves to (" + std::to_string(newPosition.x) + ","
//              + std::to_string(newPosition.y) + ")");
    Organism *neighbour = world.GetAtField(newPosition);
    if (neighbour != nullptr) {
        neighbour->Collision(this, true);
        return;
    }
    position = newPosition;
}

void Animal::Fight(Organism *attacker) {
    // fight
    if (attacker->GetStrength() >= strength) {
        Kill(attacker);
        attacker->SetPosition(position);
    } else {
        attacker->Kill(this);
    }

}
