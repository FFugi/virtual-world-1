//
// Created by ffugi on 02.04.18.
//

#include <ncurses.h>
#include "Logger.hpp"


void Logger::Log(std::string log) {
    Log(log, Color::WHITE);
}

void Logger::Log(std::string log, Color colorPair) {
    logs.push_back({log, static_cast<int>(colorPair)});
    scrollPosition = 0;
}

void Logger::ScrollDown() {
    if (logs.size() > height && scrollPosition < 0) {
        scrollPosition++;
    }
}

void Logger::ScrollUp() {
    if (logs.size() > height
        && scrollPosition > -static_cast<long>(logs.size() - height)) {
        scrollPosition--;
    }
}

void Logger::Render() {
    RenderFrame();
    RenderLogs();
}

void Logger::RenderLogs() {
    std::string output;
    for (std::size_t j = 0, i = (logs.size() > height
                                 ? logs.size() - height : 0) + scrollPosition;
         j < height; j++, i++) {
        if (i < logs.size()) {
            output = logs.at(i).value;
            move(position.y + j + 2, position.x + 1);
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
    addch(ACS_ULCORNER);
    for (std::size_t i = 1; i < 50; i++) {
        addch(ACS_HLINE);
    }
    addch(ACS_PLUS);
    for (std::size_t i = 1; i < height + 2; i++) {
        move(position.y + 1 + i, position.x);
        addch(ACS_VLINE);
    }
    move(position.y + height + 2, position.x);
    addch(ACS_PLUS);
}

void Logger::ChangePosition(Position position) {
    this->position = position;
}

std::string Logger::GetText() {
    int currentLine = logs.size() > height ? height : logs.size();
    move(position.y + currentLine + 2, position.x + 1);
    addstr("> ");
    echo();
    curs_set(1);
    char buffer[50];
    getnstr(buffer, 20);
    noecho();
    curs_set(0);
    Log(buffer);
    return std::string(buffer);
}

bool Logger::GetConfirmation(std::string message) {
    Log(message + " [Y/N]", Color::CYAN);
    world.Render();
    int input = getch();
    while (input != 'y' && input != 'Y') {
        if (input == 'n' || input == 'N') {
            return false;
        }
        input = getch();
    }
    return true;
}

void Logger::SetPosition(Position pos) {
    this->position = pos;
}
