//
// Created by ffugi on 01.04.18.
//

#include "Animal.hpp"
#include "Plant.hpp"

Animal::Animal(Position position, World &world, int initiative, int strength,
               char symbol, std::string name) : Organism(position, world,
                                                         initiative,
                                                         strength,
                                                         symbol, name) {}


void Animal::Collision(Organism *other) {
    world.Log("collision of " + FullName() + " and " + other->FullName() +
              " at " +
              " " + std::to_string(position.x) + " " + std::to_string
                      (position.y));
    // TODO check plant?
    if (dynamic_cast<Plant *>(other)) {
        other->Collision(this);
        return;
    } else if (typeid(*this).name() == typeid(*other).name()) {
        // same animals, procrastination!
        Organism *newOrganism = Procreate();
        if (newOrganism == nullptr) {
          //  world.Log(name + " cannot procreate - no space!");
            return;
        }
        world.Log("New " + newOrganism->FullName(), 1);
        world.AddOrganism(newOrganism);
        return;
    }
    // fight
    if (other->GetStrength() > strength) {
        world.Log(other->FullName() + " kills " + FullName(), 2);
        Kill();
        other->SetPosition(position);
    } else {
        world.Log(FullName() + " kills " + other->FullName(), 2);
        other->Kill();
    }
}

void Animal::Action() {
    // TODO random move
    age++;
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        // TODO log?
        return;
    }
    world.Log(FullName() + " moves to (" + std::to_string(newPosition.x) + ","
              + std::to_string(newPosition.y) + ")");
    Organism *neighbour = world.GetAtField(newPosition);
    if (neighbour != nullptr) {
        neighbour->Collision(this);
        return;
    }
    position = newPosition;
}


