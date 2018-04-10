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
#include "serialization/Serializator.hpp"

class Organism;

class World : public Serializable{
private:
    Position position;
    std::vector<Organism *> organisms;
    int width;
    int height;
    int numberOfTurn;
    Logger logger;
    bool wasOrganismAdded;
public:
    enum Command{
        NEXT_TURN,
        EXIT,
        SAVE,
        LOAD,
        ERROR
    };
    class NoPossibleFieldException : public std::exception{
    public:
        char const * what() const throw(){ return "There is no possible "
                                                   "field"; }
        ~NoPossibleFieldException() throw(){}
    };
    World(int width, int height) : position({3, 3}), width(width), height
        (height), numberOfTurn(0), logger({2, position.y + height+ 2}),
                                   wasOrganismAdded(false) {};

    ~World();

    Organism * GetAtField(Position pos);

    void AddOrganism(Organism * toAdd);
    void Render();
    Command NextTurn();
    void Log(std::string log);
    void Log(std::string log, int colorPair);
    Position GetRandomNeighbourField(Position pos);
    Position GetRandomNeighbourFreeField(Position pos);
    std::vector<Position> GetNeighbourFields(Position pos);
    std::string Serialize() override;
private:
    void RenderSignature();
    void RenderFrame();
    void RenderLegend();
    void CleanDeadOrganisms();
    void SaveToFile();
    Command GetInput();

};

#include "Organism.hpp"


#endif //VIRTUAL_WORLD_1_WORLD_HPP
