//
// Created by ffugi on 27.03.18.
//

#ifndef VIRTUAL_WORLD_1_WOLF_HPP
#define VIRTUAL_WORLD_1_WOLF_HPP


#include "Animal.hpp"

class Wolf : public Animal{
public:
    Wolf(Position position, World &world)
            : Animal(position, world, 5, 9, 'W', "Wolf") {}

public:

    Organism * Procreate() override ;

};


#endif //VIRTUAL_WORLD_1_WOLF_HPP
