//
// Created by ffugi on 26.03.18.
//

#include "Organism.hpp"

Organism::Organism(int x, int y, World &world, int initiative, int strength) :
        x(x), y(y), World(World), initiative(initiative), strength(strength) {
}

bool Organism::CompareInitiative(Organism &first, Organism &second) {
    return first.initiative < second.initiative;
}