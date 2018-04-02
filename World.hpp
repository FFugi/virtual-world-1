//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_WORLD_HPP
#define VIRTUAL_WORLD_1_WORLD_HPP

#include <vector>
#include <cstddef>
#include <string>
#include "structures.hpp"
#include "Logger.hpp"

class Organism;
class Sheep;

class World {
private:
    std::vector<Organism *> organisms;
    int width;
    int height;
    int numberOfTurn;
    Logger logger;
public:
    World();

    World(int width, int height);

    ~World();

    void AddOrganism(Organism *toAdd);
    void Render();
    bool NextTurn();
    void Log(std::string log);
    std::vector<Position> GetPossibleFields(Position pos);
private:
    void RenderFrame();

};

#include "Organism.hpp"
#include "Sheep.hpp"


#endif //VIRTUAL_WORLD_1_WORLD_HPP
