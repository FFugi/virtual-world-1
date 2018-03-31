//
// Created by ffugi on 27.03.18.
//

#ifndef VIRTUAL_WORLD_1_SHEEP_HPP
#define VIRTUAL_WORLD_1_SHEEP_HPP

#include "Organism.hpp"

class Sheep : public Organism {
public:
    Sheep(int x, int y, World &world)
    : Organism(x, y, world, 4, 4) {}

public:


};


#endif //VIRTUAL_WORLD_1_SHEEP_HPP
