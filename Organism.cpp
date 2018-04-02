//
// Created by ffugi on 26.03.18.
//

#include "Organism.hpp"


void Organism::Display(int begX, int begY){
    move(begY + position.y, begX + position.x);
    addch(symbol);
}

bool Organism::CompareInitiative(Organism &first, Organism &second) {
    return first.initiative < second.initiative;
}