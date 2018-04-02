//
// Created by ffugi on 01.04.18.
//

#include "Grass.hpp"

Grass::Grass(Position position, World &world) : Plant (position, world,
                                                          0, 'g',
                                                       "Grass") {}


void Grass::Action() {
    Plant::Action();
}


Organism *Grass::Procrastinate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch(World::NoPossibleFieldException &e){
        return nullptr;
    }
    world.Log(
            "Grass at " + std::to_string(position.x) + ", " + std::to_string
                    (position.y) + " generates new grass at: " +
            std::to_string(newPosition.x) + ", " +
            std::to_string(newPosition.y));
    return new Grass(newPosition, world);
}
