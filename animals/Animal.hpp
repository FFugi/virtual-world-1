//
// Created by ffugi on 01.04.18.
//

#ifndef VIRTUAL_WORLD_1_ANIMAL_HPP
#define VIRTUAL_WORLD_1_ANIMAL_HPP

#include <cstdlib>
#include <typeinfo>
#include <string>
#include "../Organism.hpp"

class Animal : public Organism {
public:
    Animal(Position position, World &world, int initiative,
                   int strength,
                   char symbol, std::string name, Color color) :
            Organism(position, world, initiative, strength, symbol, name,
                     color) {}

    void Collision(Organism *other, bool isAttacked) override;

    void Action() override;

protected:
    virtual void Fight(Organism *attacker);

    void Procreate(Organism *other);
};

#include "../World.hpp"


#endif //VIRTUAL_WORLD_1_ANIMAL_HPP
