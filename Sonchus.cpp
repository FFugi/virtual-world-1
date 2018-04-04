//
// Created by ffugi on 04.04.18.
//

#include "Sonchus.hpp"

void Sonchus::Action() {
    for(std::size_t i = 0; i < 3; i++) {
        Plant::Action();
    }
}

Organism *Sonchus::Procreate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch(World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Sonchus(newPosition, world);
}

void Sonchus::Display(Position beg) const {
    attron(COLOR_PAIR(3));
    Organism::Display(beg);
    attroff(COLOR_PAIR(3));
}
