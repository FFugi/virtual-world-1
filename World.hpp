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
#include "serialization/Serializer.hpp"
#include "OrganismManager.hpp"


class World : public Serializable {
private:
    Position position;
    //std::vector<Organism*> organisms;
    int width;
    int height;
    int numberOfTurn;
    Logger logger;
    OrganismManager manager;
public:
    enum class Command {
        NEXT_TURN,
        EXIT,
        SAVE,
        LOAD,
        SCROLL_UP,
        SCROLL_DOWN,
        ERROR
    };

    class NoPossibleFieldException : public std::exception {
    public:
        char const *what() const throw() {
            return "There is no possible "
                   "field";
        }

        ~NoPossibleFieldException() throw() {}
    };

    World(int width, int height) : position({3, 3}),
                                   width(width), height(height),
                                   numberOfTurn(0),
                                   logger({2, position.y + height + 2}, 21,
                                          *this),
                                    manager(*this){};

    virtual ~World();

    Organism *GetAtField(Position pos);

    void AddOrganism(Organism *toAdd);

    void Render();

    Command NextTurn();

    void Log(std::string log);

    void Log(std::string log, Color color);

    Position GetRandomNeighbourField(Position pos);

    Position GetRandomNeighbourFreeField(Position pos);

    std::vector<Position> GetNeighbourFields(Position pos);

    std::string Serialize() override;

    void Deserialize(std::string data) override;

    void MoveOrganism(Organism* org, Position newPosition);

private:
    void RenderSignature();

    void RenderFrame();

    void RenderLegend();

    void SaveToFile();

    void LoadFromFile();

    void ResetWorld();

    Command GetInput();

    Organism * GetOrganismOfName(std::string name);

};


#endif //VIRTUAL_WORLD_1_WORLD_HPP
