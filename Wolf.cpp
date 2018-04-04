//
// Created by ffugi on 27.03.18.
//

#include "Wolf.hpp"


Organism *Wolf::Procrastinate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Wolf(newPosition, world);
}

