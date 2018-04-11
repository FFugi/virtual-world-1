//
// Created by ffugi on 01.04.18.
//

#ifndef VIRTUAL_WORLD_1_GRASS_HPP
#define VIRTUAL_WORLD_1_GRASS_HPP


#include "Plant.hpp"

class Grass : public Plant {
public:
    Grass(Position position, World &world) :
            Plant(position, world, 0, 'g', "Grass") {};

    Grass(World &world) : Plant({0,0}, world, 0, 'g', "Grass") {};

    void Action() override;

    Organism *Procreate() override;

    void Display(Position beg) const override;
};


#endif //VIRTUAL_WORLD_1_GRASS_HPP
