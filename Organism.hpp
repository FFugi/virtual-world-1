//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_ORGANISM_HPP
#define VIRTUAL_WORLD_1_ORGANISM_HPP

#include "World.hpp"

class World;

class Organism {
protected:
    int x;
    int y;
    int initiative;
    int strength;
    World &world;

public:
    Organism(int x, int y, World &world, int initiative, int strength);
    virtual void Collision() = 0;
    virtual void Display() = 0;
    virtual void Action() = 0;

    static bool CompareInitiative(Organism &first, Organism &second);
};


#endif //VIRTUAL_WORLD_1_ORGANISM_HPP
