//
// Created by ffugi on 04.04.18.
//

#include "Sonchus.hpp"

void Sonchus::Action() {
    for(std::size_t i = 0; i < 3; i++) {
        Plant::Action();
    }
}

Organism *Sonchus::GetNewOrganism() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch(World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Sonchus(newPosition, world);
}
