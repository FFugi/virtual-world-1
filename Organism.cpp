//
// Created by ffugi on 26.03.18.
//

#include "Organism.hpp"


void Organism::Display(){
    move(position.y, position.x);
    addch(symbol);
}

bool Organism::CompareInitiative(Organism &first, Organism &second) {
    return first.initiative < second.initiative;
}