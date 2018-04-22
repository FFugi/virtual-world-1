//
// Created by ffugi on 04.04.18.
//

#ifndef VIRTUAL_WORLD_1_TURTLE_HPP
#define VIRTUAL_WORLD_1_TURTLE_HPP


#include "Animal.hpp"

class Tortoise: public Animal {
public:
    Tortoise(Position position, World &world)
            : Animal(position, world, 2, 1, 'T', "Tortoise", Color::WHITE) {}

    Tortoise(World &world) : Animal({0,0}, world, 2, 1, 'T', "Tortoise",
                                  Color::WHITE) {}

    void Collision(Organism *other, bool isAttacked) override;

    void Action() override;

    Organism *GetNewOrganism() override;
};


#endif //VIRTUAL_WORLD_1_TURTLE_HPP
