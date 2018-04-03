//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_WORLD_HPP
#define VIRTUAL_WORLD_1_WORLD_HPP

#include <vector>
#include <algorithm>
#include <cstddef>
#include <exception>
#include <string>
#include "structures.hpp"
#include "Logger.hpp"
#include "Organism.hpp"

class Organism;
class Sheep;

class World {
private:
    Position position;
    std::vector<Organism *> organisms;
    int width;
    int height;
    int numberOfTurn;
    Logger logger;
public:
    class NoPossibleFieldException : public std::exception{
    public:
        char const * what() const throw(){ return "There is no possible "
                                                   "field"; }
        ~NoPossibleFieldException() throw(){}
    };
    World();

    World(int width, int height);

    ~World();

    Organism * GetAtField(Position pos);

    void AddOrganism(Organism * toAdd);
    void Render();
    void NextTurn();
    void Log(std::string log);
    Position GetRandomNeighbourField(Position pos);
    Position GetRandomNeighbourFreeField(Position pos);
private:
    std::vector<Position> GetNeighbourFields(Position pos);
    void RenderFrame();
    void CleanDeadOrganisms();

};

#include "Organism.hpp"
#include "Sheep.hpp"


#endif //VIRTUAL_WORLD_1_WORLD_HPP
