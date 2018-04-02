//
// Created by ffugi on 27.03.18.
//

#ifndef VIRTUAL_WORLD_1_WOLF_HPP
#define VIRTUAL_WORLD_1_WOLF_HPP


#include "Organism.hpp"

class Wolf : public Organism {
public:
    Wolf(Position position, World &world)
            : Organism(position, world, 5, 9, 'W', "Wolf") {}

public:

};


#endif //VIRTUAL_WORLD_1_WOLF_HPP
