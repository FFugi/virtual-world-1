//
// Created by ffugi on 22.04.18.
//

#ifndef VIRTUAL_WORLD_1_MENU_HPP
#define VIRTUAL_WORLD_1_MENU_HPP


#include "World.hpp"
#include <set>

class Menu {
    World *world;
    unsigned long cursorPosition;
    Position position;
    const unsigned marginLeft;
    const unsigned width;

    std::vector<std::pair<std::string, unsigned >> parameters;
    enum class Command {
        GO_UP,
        GO_DOWN,
        INCREMENT,
        DECREMENT,
        START_SIMULATION,
        EXIT,
        UNKNOWN
    };
public:
    Menu(Position position) : world(nullptr), cursorPosition(0),
                              position(position), marginLeft(3), width(50) {
        parameters.push_back({"width", 20});
        parameters.push_back({"height", 20});
        parameters.push_back({"Fox", 2});
        parameters.push_back({"Sheep", 2});
        parameters.push_back({"Wolf", 2});
        parameters.push_back({"Antelope", 2});
        parameters.push_back({"Tortoise", 2});
        parameters.push_back({"Grass", 2});
        parameters.push_back({"Guarana", 2});
        parameters.push_back({"Hogweed", 2});
        parameters.push_back({"Sonchus", 2});
        parameters.push_back({"Wolf Berry", 2});
        parameters.push_back({"Human", 1});
    }

    ~Menu();

    bool Execute();

private:
    void CreateWorld();

    void ExecuteCommand(Command cmd);

    Command GetCommand();

    void Render();

    unsigned Capacity();

    unsigned Capacity(unsigned width, unsigned height);

    unsigned OrganismsCount();

    unsigned OrganismsLimit();

    unsigned OrganismsLimit(unsigned width, unsigned height);

    void RenderParameters();

    void RenderFrame() const;
};


#endif //VIRTUAL_WORLD_1_MENU_HPP
