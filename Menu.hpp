//
// Created by ffugi on 22.04.18.
//

#ifndef VIRTUAL_WORLD_1_MENU_HPP
#define VIRTUAL_WORLD_1_MENU_HPP


#include "World.hpp"
#include <set>

class Menu {
    World *world;

    std::vector<std::pair<std::string, unsigned >> parameters;
    unsigned long menuPosition;
//    enum class Command
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
    Menu() : world(nullptr), menuPosition(0) {
        parameters.push_back({"width", 20});
        parameters.push_back({"height", 20});
        parameters.push_back({"fox", 2});
        parameters.push_back({"sheep", 2});
        parameters.push_back({"wolf", 2});
        parameters.push_back({"antelope", 2});
        parameters.push_back({"turtle", 2});
        parameters.push_back({"grass", 2});
        parameters.push_back({"guarana", 2});
        parameters.push_back({"hogweed", 2});
        parameters.push_back({"sonchus", 2});
        parameters.push_back({"wolfBerry", 2});
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
};


#endif //VIRTUAL_WORLD_1_MENU_HPP
