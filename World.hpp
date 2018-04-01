//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_WORLD_HPP
#define VIRTUAL_WORLD_1_WORLD_HPP

#include <vector>
#include "structures.hpp"

class Organism;
class Sheep;

class World {
private:
    std::vector<Organism *> organisms;
    int width;
    int height;
    int numberOfTurn;
public:
    World();

    World(int width, int height);

    ~World();

    void AddOrganism(Organism *toAdd);
    void Render();
    bool NextTurn();
    std::vector<Position> GetPossibleFields(Position pos);


};

#include "Organism.hpp"
#include "Sheep.hpp"


#endif //VIRTUAL_WORLD_1_WORLD_HPP
