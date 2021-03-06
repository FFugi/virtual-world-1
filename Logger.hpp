//
// Created by ffugi on 02.04.18.
//

#ifndef VIRTUAL_WORLD_1_LOGGER_HPP
#define VIRTUAL_WORLD_1_LOGGER_HPP


#include <string>
#include <vector>
#include "Position.hpp"
#include "Color.hpp"

class World;

class Logger {
private:
    struct Log {
        std::string value;
        int color;
    };
    std::vector<Log> logs;
    Position position;
    long scrollPosition;
    unsigned int height;
    World &world;
public:
    Logger(unsigned int height, World &world)
            : position({0, 0}), scrollPosition(0), height(height),
              world(world) {}

    void Log(std::string log);

    void Log(std::string log, Color colorPair);

    void Reset();

    void ChangePosition(Position position);

    std::string GetText();

    bool GetConfirmation(std::string message);

    void Render();

    void ScrollUp();

    void ScrollDown();

    void SetPosition(Position pos);

private:
    void RenderFrame();

    void RenderLogs();
};

#include "World.hpp"

#endif //VIRTUAL_WORLD_1_LOGGER_HPP
