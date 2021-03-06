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
#include "Position.hpp"
#include "Logger.hpp"
#include "Organism.hpp"
#include "serialization/Serializer.hpp"
#include "OrganismManager.hpp"


class World : public Serializable {
private:
    Position position;
    int width;
    int height;
    int numberOfTurn;
    Logger logger;
    OrganismManager manager;
    enum class LoadingStatus{
        SUCCESS,
        FAIL,
        ABORT
    };
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
                                   logger(21,
                                          *this),
                                   manager(*this) {
        SetLoggerPosition();
    };

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

    std::string Serialize() const override;

    void Deserialize(std::string data) override;

    void MoveOrganism(Organism *org, Position newPosition);

    int GetWidth() const;

    int GetHeight() const;

private:
    void RenderSignature();

    void RenderFrame();

    void RenderLegend();

    void SaveToFile();

    LoadingStatus LoadFromFile();

    void ResetWorld();

    Command GetInput();

    void SetLoggerPosition();
};


#endif //VIRTUAL_WORLD_1_WORLD_HPP
