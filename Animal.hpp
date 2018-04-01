//
// Created by ffugi on 01.04.18.
//

#ifndef VIRTUAL_WORLD_1_ANIMAL_HPP
#define VIRTUAL_WORLD_1_ANIMAL_HPP

#include <cstdlib>
#include <string>
#include "Organism.hpp"

class Animal : public Organism {
public:
    Animal(Position position, World &world, int initiative, int strength,
           char symbol);

    void Collision() override;

    void Action() override;

};

#include "World.hpp"


#endif //VIRTUAL_WORLD_1_ANIMAL_HPP
