//
// Created by ffugi on 01.04.18.
//

#include "Grass.hpp"


void Grass::Action() {
    Plant::Action();
}


Organism *Grass::GetNewOrganism() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch(World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Grass(newPosition, world);
}
