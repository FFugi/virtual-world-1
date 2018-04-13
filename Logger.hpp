//
// Created by ffugi on 02.04.18.
//

#ifndef VIRTUAL_WORLD_1_LOGGER_HPP
#define VIRTUAL_WORLD_1_LOGGER_HPP


#include <string>
#include <vector>
#include "structures.hpp"

class Logger {
private:
    struct Log{
        std::string value;
        int color;
    };
    std::vector<Log> logs;
    Position position;
    long scrollPosition;
    unsigned int height;
public:
    enum Color {
        WHITE,
        GREEN,
        RED,
        YELLOW,
        MAGENTA,
        CYAN
    };
    Logger(Position position, unsigned int height);
    void Log(std::string log);
    void Log(std::string log, Color colorPair);
    void Reset();
    void ChangePosition(Position position);
    std::string GetText();
    void Render();
    void ScrollUp();
    void ScrollDown();
private:
    void RenderFrame();
    void RenderLogs();
};


#endif //VIRTUAL_WORLD_1_LOGGER_HPP
