//
// Created by ffugi on 21.04.18.
//

#ifndef VIRTUAL_WORLD_1_HUMAN_HPP
#define VIRTUAL_WORLD_1_HUMAN_HPP


#include "Animal.hpp"

class Human : public Animal {
private:
    int ageWhenPowerWasUsed;
public:
    Human(Position position, World &world) : Animal(position, world, 4,
                                                    5, 'H', "Human",
                                                    Color::YELLOW) {}

    Human(World &world) : Animal({0, 0}, world, 4, 5, 'H', "Human",
                                 Color::YELLOW) {}

    void Action() override;

   // void Collision(Organism *other, bool isAttacked) override;

    Organism * Procreate() override;
};


#endif //VIRTUAL_WORLD_1_HUMAN_HPP
