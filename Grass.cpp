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


Organism *Grass::Procreate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch(World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Grass(newPosition, world);
}

void Grass::Display(Position beg) const {
    attron(COLOR_PAIR(1));
    Organism::Display(beg);
    attroff(COLOR_PAIR(1));
}
