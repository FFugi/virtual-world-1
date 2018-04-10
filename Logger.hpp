//
// Created by ffugi on 02.04.18.
//

#ifndef VIRTUAL_WORLD_1_LOGGER_HPP
#define VIRTUAL_WORLD_1_LOGGER_HPP


#include <string>
#include "structures.hpp"

class Logger {
private:
    Position position;
    int currentLine;
public:
    Logger(Position position);
    void Log(std::string log);
    void Log(std::string log, int colorPair);
    void RenderFrame();
    void Reset();
    void ChangePosition(Position position);
    std::string GetText();
};


#endif //VIRTUAL_WORLD_1_LOGGER_HPP
