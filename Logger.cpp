//
// Created by ffugi on 02.04.18.
//

#include <ncurses.h>
#include "Logger.hpp"

Logger::Logger(Position position) : position(position), currentLine(0) {}

void Logger::Log(std::string log) {
    Log(log, Logger::WHITE);
}

void Logger::Log(std::string log, Color colorPair) {
    logs.push_back({log, colorPair});
}

void Logger::Render() {
    RenderFrame();
    int line = 0;
    std::string output;
    for (auto log : logs) {
        output = log.value;
        move(position.y + line+ 2, position.x + 1);
        output = "> " + output;
        attron(COLOR_PAIR(log.color) | A_BOLD);
        addstr(output.c_str());
        attroff(COLOR_PAIR(log.color) | A_BOLD);
        line++;
    }

}

void Logger::RenderFrame() {
    move(position.y, position.x + 5);
    addstr("<=-Logger-=>");
    move(position.y + 1, position.x);
    addch('#');
    for (std::size_t i = 1; i < 50; i++) {
        addch('-');
    }
    addch('>');
    for (std::size_t i = 1; i < 20; i++) {
        move(position.y + 1 + i, position.x);
        addch('|');
    }
    move(position.y + 21, position.x);
    addch('V');
}

void Logger::Reset() {
    currentLine = 0;
}

void Logger::ChangePosition(Position position) {
    this->position = position;
}

std::string Logger::GetText() {
    move(position.y + currentLine + 2, position.x + 1);
    echo();
    curs_set(1);
    char buffer[50];
    getnstr(buffer, 10);
    noecho();
    curs_set(0);
    currentLine++;
    return std::string(buffer);
}
