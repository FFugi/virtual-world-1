//
// Created by ffugi on 27.03.18.
//

#include "Sheep.hpp"

void Sheep::Action() {
    Animal::Action();
}


Organism *Sheep::Procreate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Sheep(newPosition, world);
}
