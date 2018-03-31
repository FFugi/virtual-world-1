//
// Created by ffugi on 27.03.18.
//

#ifndef VIRTUAL_WORLD_1_WOLF_HPP
#define VIRTUAL_WORLD_1_WOLF_HPP


#include "Organism.hpp"

class Wolf : public Organism {
public:
    Wolf(int x, int y, World &world)
            : Organism(x, y, world, 5, 9) {}

public:

};


#endif //VIRTUAL_WORLD_1_WOLF_HPP
