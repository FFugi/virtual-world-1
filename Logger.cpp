//
// Created by ffugi on 02.04.18.
//

#include <ncurses.h>
#include "Logger.hpp"

Logger::Logger(Position position) : position(position), currentLine(0) {}

void Logger::Log(std::string log) {
    move(position.y + currentLine, position.x);
    log = "> "+log;
    addstr(log.c_str());
    currentLine++;
}

void Logger::Reset() {
    currentLine = 0;
}

void Logger::ChangePosition(Position position) {
    this->position = position;
}
