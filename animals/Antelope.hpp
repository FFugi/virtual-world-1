//
// Created by ffugi on 06.04.18.
//

#ifndef VIRTUAL_WORLD_1_ANTELOPE_HPP
#define VIRTUAL_WORLD_1_ANTELOPE_HPP


#include "Animal.hpp"

class Antelope : public Animal {
public:
    Antelope(Position position, World &world) : Animal(position, world, 4,
                                                       4, 'A', "Antelope") {}

    Antelope(World &world) : Animal({0,0}, world, 4, 4, 'A', "Antelope") {}

    void Collision(Organism *other, bool isAttacked) override;

    void Action() override;

    Organism *Procreate() override;

    void Display(Position beg) const override;

};


#endif //VIRTUAL_WORLD_1_ANTELOPE_HPP
