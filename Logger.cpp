//
// Created by ffugi on 02.04.18.
//

#include <ncurses.h>
#include "Logger.hpp"

Logger::Logger(Position position) : position(position), currentLine(0) {}

void Logger::Log(std::string log) {
    move(position.y + currentLine + 2, position.x + 1);
    log = "> "+log;
    addstr(log.c_str());
    currentLine++;
}

void Logger::RenderFrame() {
    move(position.y, position.x + 5);
    addstr("<=-Logger-=>");
    move(position.y + 1, position.x);
    addch('#');
    for(std::size_t i = 1; i < 50; i++){
        addch('-');
    }
    addch('>');
    for(std::size_t i = 1; i < 20; i++){
        move(position.y + 1 + i, position.x);
        addch('|');
    }
    move(position.y + 21 , position.x);
    addch('V');
}

void Logger::Reset() {
    currentLine = 0;
}

void Logger::ChangePosition(Position position) {
    this->position = position;
}
