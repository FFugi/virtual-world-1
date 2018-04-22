//
// Created by ffugi on 22.04.18.
//

#include "Menu.hpp"

bool Menu::Execute() {
    bool willContinue = true;
    while (willContinue) {
        if (world == nullptr) {
            Render();
            Command cmd = GetCommand();
            if (cmd == Command::EXIT) {
                return false;
            }
            ExecuteCommand(cmd);
        } else {
            World::Command cmd = world->NextTurn();
            world->Render();
            if (cmd == World::Command::EXIT) {
                willContinue = false;
            }
        }
    }

    return true;
}

Menu::Command Menu::GetCommand() {
    int cmd = getch();
    switch (cmd) {
        case 'q':
        case 'Q':
            return Command::EXIT;
        case KEY_UP:
            return Command::GO_UP;
        case KEY_DOWN:
            return Command::GO_DOWN;
        case KEY_LEFT:
            return Command::DECREMENT;
        case KEY_RIGHT:
            return Command::INCREMENT;
        default:
            return Command::UNKNOWN;
    }
}

void Menu::ExecuteCommand(Command cmd) {
    auto &val = parameters.at(menuPosition).second;
    switch (cmd) {
        case Command::GO_UP:
            if (menuPosition == 0) {
                menuPosition = parameters.size() - 1;
            } else {
                menuPosition--;
            }
            break;
        case Command::GO_DOWN:
            menuPosition++;
            menuPosition %= parameters.size();
            break;
        case Command::INCREMENT:
            if(OrganismsCount() < OrganismsLimit()) {
                val++;
            }
            break;
        case Command::DECREMENT:
            if(val!=0) {
                val--;
            }
            break;
        default:
            break;
    }
}

void Menu::Render() {
    clear();
    unsigned startY = 0;
    for (auto count : parameters) {
        move(2 + startY, 2);
        if (menuPosition == startY) {
            attron(A_REVERSE);
        }
        printw("%-5s %-10s", std::to_string(count.second).c_str(),
               count.first.c_str());
        if (menuPosition == startY) {
            attroff(A_REVERSE);
        }
        startY++;
    }
    move(2 + 1 + startY, 2);
    printw("%-5s Total", std::to_string(OrganismsCount()).c_str());
    move(2 + 2 + startY, 2);
    printw("%-5s Start organisms limit",
           std::to_string(OrganismsLimit()).c_str());
    move(2 + 3 + startY, 2);
    printw("%-5s free fields to fill",
           std::to_string(OrganismsLimit()-OrganismsCount()).c_str());
    refresh();
}

void Menu::CreateWorld() {
    world = new World(width, height);
}

unsigned Menu::Capacity() {
    return Capacity(width, height);
}

unsigned Menu::Capacity(unsigned width, unsigned height) {
    return width * height;
}

Menu::~Menu() {
    if (world != nullptr) {
        delete world;
    }
}

unsigned Menu::OrganismsCount() {
    unsigned sum = 0;
    for (auto &num : parameters) {
        sum += num.second;
    }
    return sum;
}

unsigned Menu::OrganismsLimit() {
    return Capacity()/10;
}
