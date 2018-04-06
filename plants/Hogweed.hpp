//
// Created by ffugi on 06.04.18.
//

#ifndef VIRTUAL_WORLD_1_HOGWEED_HPP
#define VIRTUAL_WORLD_1_HOGWEED_HPP


#include "Plant.hpp"
#include "../animals/Animal.hpp"

class Hogweed : public Plant {
public:
    Hogweed(Position position, World &world) :
    Plant(position, world, 0, 'h', "Hogweed") {};

    void Action() override;

    void Collision(Organism *other, bool isAttacked) override ;

    Organism *Procreate() override;

    void Display(Position beg) const override;
};


#endif //VIRTUAL_WORLD_1_HOGWEED_HPP
