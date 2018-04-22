//
// Created by ffugi on 04.04.18.
//

#ifndef VIRTUAL_WORLD_1_FOX_HPP
#define VIRTUAL_WORLD_1_FOX_HPP

#include "Animal.hpp"

class Fox : public Animal {
public:
    Fox(Position position, World &world)
            : Animal(position, world, 7, 3, 'F', "Fox", Color::RED) {}

    Fox(World &world): Animal({0,0}, world, 7, 3, 'F', "Fox", Color::RED) {}

    void Action() override;

    Organism *GetNewOrganism() override;
};

#endif //VIRTUAL_WORLD_1_FOX_HPP
