//
// Created by ffugi on 04.04.18.
//

#ifndef VIRTUAL_WORLD_1_FOX_HPP
#define VIRTUAL_WORLD_1_FOX_HPP


#include "Animal.hpp"

class Fox : public Animal {
public:
    Fox(Position position, World &world)
            : Animal(position, world, 7, 3, 'F', "Fox") {}

    void Action() override ;
    Organism * Procreate() override;
    void Display(Position beg) const override;
};


#endif //VIRTUAL_WORLD_1_FOX_HPP
