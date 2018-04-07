//
// Created by ffugi on 04.04.18.
//

#ifndef VIRTUAL_WORLD_1_TURTLE_HPP
#define VIRTUAL_WORLD_1_TURTLE_HPP


#include "Animal.hpp"

class Turtle : public Animal {
public:
    Turtle(Position position, World &world)
            : Animal(position, world, 2, 1, 'T', "Turtle") {}

    void Collision(Organism *other, bool isAttacked) override;

    void Action() override;

    Organism *Procreate() override;

    void Display(Position beg) const override;
};


#endif //VIRTUAL_WORLD_1_TURTLE_HPP