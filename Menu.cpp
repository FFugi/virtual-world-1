//
// Created by ffugi on 22.04.18.
//

#include "Menu.hpp"
#include "OrganismFactory.hpp"

bool Menu::Execute() {
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
            delete world;
            world = nullptr;
            return true;
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
        case 10:
            return Command::START_SIMULATION;
        default:
            return Command::UNKNOWN;
    }
}

void Menu::ExecuteCommand(Command cmd) {
    auto &val = parameters.at(cursorPosition).second;
    switch (cmd) {
        case Command::GO_UP:
            if (cursorPosition == 0) {
                cursorPosition = parameters.size() - 1;
            } else {
                cursorPosition--;
            }
            break;
        case Command::GO_DOWN:
            cursorPosition++;
            cursorPosition %= parameters.size();
            break;
        case Command::INCREMENT:
            // when menuPos isn't pointing at width or height
            if (parameters.at(cursorPosition).first != "width" &&
                parameters.at(cursorPosition).first != "height") {
                if (OrganismsCount() < OrganismsLimit()) {
                    if (parameters.at(cursorPosition).first == "Human" &&
                        val == 1) {
                        val = 1;
                    } else {
                        val++;
                    }
                }
            } else {
                val++;
            }
            break;
        case Command::DECREMENT:
            if (val != 0) {
                // when menuPos isn't pointing at width or height
                if (parameters.at(cursorPosition).first != "width" &&
                    parameters.at(cursorPosition).first != "height") {
                    val--;
                } else {
                    if (parameters.at(cursorPosition).first == "width") {
                        if (OrganismsLimit(parameters.at(0).second - 1,
                                           parameters.at(1).second) >
                            OrganismsCount()) {
                            val--;
                        }
                    } else if (parameters.at(cursorPosition).first ==
                               "height") {
                        if (OrganismsLimit(parameters.at(0).second,
                                           parameters.at(1).second - 1) >
                            OrganismsCount()) {
                            val--;
                        }
                    }
                }
            }
            break;
        case Command::START_SIMULATION:
            CreateWorld();
            break;
        default:
            break;
    }
}

void Menu::Render() {
    clear();

    RenderFrame();
    RenderParameters();
    refresh();
}

void Menu::RenderFrame() const {
    move(position.y, position.x);
    addch(ACS_ULCORNER);
    for (std::size_t i = 1; i < width; i++) {
        addch(ACS_HLINE);
    }
    addch(ACS_PLUS);
    for (std::size_t i = 1; i < parameters.size() + 7; i++) {
        move(position.y + i, position.x);
        addch(ACS_VLINE);
    }
    move(position.y + parameters.size() + 7, position.x);
    addch(ACS_PLUS);
}

void Menu::RenderParameters() {
    unsigned startY = 0;
    for (auto count : parameters) {
        move(position.y + 2 + startY, position.x + marginLeft);
        if (cursorPosition == startY) {
            attron(A_REVERSE);
        }
        printw("%-5s %-10s", std::__cxx11::to_string(count.second).c_str(),
               count.first.c_str());
        if (cursorPosition == startY) {
            attroff(A_REVERSE);
        }
        startY++;
    }
    move(position.y + 2 + ++startY, position.x + marginLeft);
    printw("%-5s Total", std::__cxx11::to_string(OrganismsCount()).c_str());
    move(position.y + 2 + ++startY, position.x + marginLeft);
    printw("%-5s Organisms limit",
           std::__cxx11::to_string(OrganismsLimit()).c_str());
    move(position.y + 2 + ++startY, position.x + marginLeft);
    printw("%-5s Free fields to fill", std::__cxx11::to_string(
                   OrganismsLimit() - OrganismsCount()).c_str());
}

void Menu::CreateWorld() {
    world = new World(parameters.at(0).second,
                      parameters.at(1).second);
    Position randomPos;
    OrganismFactory factory;
    for (auto &org : parameters) {
        if (org.first != "width" && org.first != "height") {
            for (std::size_t i = 0; i < org.second; i++) {
                do {
                    randomPos = {
                            static_cast<int>(rand() % parameters.at(0).second),
                            static_cast<int>(rand() %
                                             parameters.at(1).second)};
                } while (world->GetAtField(randomPos) != nullptr);
                Organism *toAdd = factory.GetOrganism(org.first, randomPos,
                                                      *world);
                if (toAdd != nullptr) {
                    world->AddOrganism(toAdd);
                }
            }
        }
    }
}

unsigned Menu::Capacity() {
    return Capacity(parameters.at(0).second,
                    parameters.at(1).second);
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
        if (num.first != "height" && num.first != "width") {
            sum += num.second;
        }
    }
    return sum;
}

unsigned Menu::OrganismsLimit() {
    return Capacity() / 10;
}

unsigned Menu::OrganismsLimit(unsigned width, unsigned height) {
    return Capacity(width, height) / 10;
}
