//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_ORGANISM_HPP
#define VIRTUAL_WORLD_1_ORGANISM_HPP

#include <ncurses.h>
#include "structures.hpp"

class World;

class Organism {
protected:
    Position position;
    World &world;
    int initiative;
    int strength;
    char symbol;
    int age;

public:
    Organism(Position position, World &world, int initiative, int strength, char
    symbol) :
            position(position), world(world), initiative(initiative),
            strength(strength), symbol(symbol), age(0) {}

    virtual void Collision() = 0;

    virtual void Display(int begX, int bexY);

    virtual void Action() = 0;

    static bool CompareInitiative(Organism &first, Organism &second);
};


#endif //VIRTUAL_WORLD_1_ORGANISM_HPP
