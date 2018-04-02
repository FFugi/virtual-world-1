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
    world.Log("collision of " + name + " and " + other->name + " at " + " " +
              std::to_string(position.x) + " " + std::to_string(position.y));
    // TODO check plant?
    if (dynamic_cast<Plant*>(other)){
        other->Collision(this);
    }
    if (typeid(*this).name() == typeid(*other).name()) {
        // same animals, procrastination!
        Organism * newOrganism = Procrastinate();
        if(newOrganism == nullptr){
            world.Log("Cannot procrastinate - no space!");
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
