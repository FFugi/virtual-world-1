//
// Created by ffugi on 27.03.18.
//

#ifndef VIRTUAL_WORLD_1_SHEEP_HPP
#define VIRTUAL_WORLD_1_SHEEP_HPP

#include "Animal.hpp"

class Sheep : public Animal{
public:

public:

    Sheep(Position position, World &world);

    void Action() override;

    Organism * Procreate() override ;

};


#endif //VIRTUAL_WORLD_1_SHEEP_HPP
