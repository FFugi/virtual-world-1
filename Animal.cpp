//
// Created by ffugi on 01.04.18.
//

#include "Animal.hpp"

Animal::Animal(Position position, World &world, int initiative, int strength,
               char symbol, std::string name) : Organism(position, world,
                                                         initiative,
                                                         strength,
                                                         symbol, name) {}


void Animal::Collision(Organism *other) {
    world.Log("collision of " + name + " and " + other->name + " at " + " " +
              std::to_string(position.x) + " " + std::to_string(position.y));
    // TODO check plant?
    if (typeid(*this).name() == typeid(*other).name()) {
        // same animals, procrastination!
        world.Log("same!");
        Organism * newOrganism = Procrastinate();
        if(newOrganism == nullptr){
            // TODO log
            return;
        }
        world.AddOrganism(newOrganism);
        return;
    }
    world.Log("not same!");
}

void Animal::Action() {
    // TODO random move
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourField(position);
    }
    catch(World::NoPossibleFieldException &e){
        // TODO log?
        return;
    }
    Organism *neighbour = world.GetAtField(newPosition);
    age++;
    if (neighbour != nullptr) {
        neighbour->Collision(this);
        return;
    }
    position = newPosition;
}
