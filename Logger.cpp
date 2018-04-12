//
// Created by ffugi on 02.04.18.
//

#include <ncurses.h>
#include "Logger.hpp"

Logger::Logger(Position position, unsigned int height)
        : position(position), currentLine(0), scrollPosition(0), height
        (height) {}

void Logger::Log(std::string log) {
    Log(log, Logger::WHITE);
}

void Logger::Log(std::string log, Color colorPair) {
    logs.push_back({log, colorPair});
    scrollPosition = 0;
}

void Logger::ScrollUp() {
    if(scrollPosition < static_cast<int>(logs.size() - height)) {
        scrollPosition++;
    }
}

void Logger::ScrollDown() {
    if(logs.size() > height) {
        scrollPosition--;
    }
}

void Logger::Render() {
    RenderFrame();
    int line = 0;
    int begLine = 0;
    std::string output;
    if (logs.size() > height) {
        begLine = (int)height - (int)logs.size();
    }
    for (std::size_t i = 0; i < logs.size(); i++) {
        line = begLine + i + scrollPosition;
        if (line >= 0 && line < (int)height) {
            output = logs.at(i).value;
            move(position.y + line + 2, position.x + 1);
            output = "> " + output;
            attron(COLOR_PAIR(logs.at(i).color) | A_BOLD);
            addstr(output.c_str());
            attroff(COLOR_PAIR(logs.at(i).color) | A_BOLD);
        }
    }
}

void Logger::RenderFrame() {
    move(position.y, position.x + 5);
    addstr("<=-Logger-=>");
    move(position.y + 1, position.x);
    addch('O');
    for (std::size_t i = 1; i < 50; i++) {
        addch('-');
    }
    addch('>');
    for (std::size_t i = 1; i < height + 2; i++) {
        move(position.y + 1 + i, position.x);
        addch('|');
    }
    move(position.y + height + 2, position.x);
    addch('O');
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
