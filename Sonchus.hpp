//
// Created by ffugi on 04.04.18.
//

#ifndef VIRTUAL_WORLD_1_SONCHUS_HPP
#define VIRTUAL_WORLD_1_SONCHUS_HPP


#include "Plant.hpp"

class Sonchus :public Plant{
public:
    Sonchus(Position position, World &world):
            Plant(position, world, 0, 's', "Sonchus") {};

    void Action() override;

    Organism * Procreate() override;

    void Display(Position beg) const override;

};


#endif //VIRTUAL_WORLD_1_SONCHUS_HPP
