//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_WORLD_HPP
#define VIRTUAL_WORLD_1_WORLD_HPP

#include <vector>
#include "Organism.hpp"

class Organism;

class World {
private:
    std::vector<Organism> organisms;
    int width;
    int lenght;
    int numberOfTurn;

public:
    World();

    World(int width, int length);

    ~World();

    bool NextTurn();

    void Render();

};


#endif //VIRTUAL_WORLD_1_WORLD_HPP
