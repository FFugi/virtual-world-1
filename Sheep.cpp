//
// Created by ffugi on 27.03.18.
//

#include "Sheep.hpp"

Sheep::Sheep(Position position, World &world) : Animal(position, world, 4,
                                                  4, 'S', "Sheep") {}



void Sheep::Action() {
    Animal::Action();
}


Organism *Sheep::Procrastinate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Sheep(newPosition, world);
}
