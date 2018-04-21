//
// Created by ffugi on 26.03.18.
//
#include <ncurses.h>
#include "World.hpp"
#include "animals/Fox.hpp"
#include "animals/Wolf.hpp"
#include "animals/Turtle.hpp"
#include "animals/Antelope.hpp"
#include "animals/Sheep.hpp"
#include "plants/Grass.hpp"
#include "plants/Guarana.hpp"
#include "plants/Hogweed.hpp"
#include "plants/WolfBerry.hpp"
#include "plants/Sonchus.hpp"
#include "Color.hpp"

void World::AddOrganism(Organism *toAdd) {
    manager.AddOrganism(toAdd);
}

void World::MoveOrganism(Organism *org, Position newPosition) {
    manager.MoveOrganism(*org, newPosition);
}

void World::Render() {
    clear();
    RenderFrame();
    logger.Render();
    manager.RenderOrganisms(position);
    RenderLegend();
    RenderSignature();
    refresh();
}

Organism *World::GetAtField(Position pos) {
    return manager.GetAtField(pos);
}

World::~World() {
    manager.RemoveAllOrganisms();
    endwin();
}

void World::Log(std::string log) {
    logger.Log(std::move(log));
}

void World::Log(std::string log, Color color) {
    logger.Log(std::move(log), color);
}

World::Command World::GetInput() {
    int input = getch();
    return input == ' ' ? NEXT_TURN :
           input == 'q' ? EXIT :
           input == 's' ? SAVE :
           input == 'l' ? LOAD :
           input == 'k' ? SCROLL_UP :
           input == 'j' ? SCROLL_DOWN :
           ERROR;
}

World::Command World::NextTurn() {
    Command cmd = GetInput();
    while (cmd != NEXT_TURN && cmd != EXIT) {
        switch (cmd) {
            case SAVE:
                SaveToFile();
                break;

            case LOAD:
                LoadFromFile();
                break;

            case SCROLL_UP:
                logger.ScrollUp();
                break;

            case SCROLL_DOWN:
                logger.ScrollDown();
                break;

            default:
                Log("Unknown command, please try again!", Color::YELLOW);
                break;
        }
        Render();
        cmd = GetInput();
    }
    logger.Log("Turn number: " + std::to_string(numberOfTurn));
    manager.NextTurn();
    numberOfTurn++;
    return cmd;
}

void World::RenderFrame() {
    for (int y = position.y + 1, real = 0; y <= position.y + height; real++,
            y++) {
        move(y, position.x - 1);
        addch(std::to_string(real % 10).at(0));
        if (real % 10 == 0) {
            move(y, position.x - 2);
            addch(std::to_string(real % 100).at(0));
        }
        move(y, position.x);
        addch('|');
        move(y, position.x + width + 1);
        addch('|');
    }
    for (int x = position.x + 1, real = 0;
         x <= position.x + width; real++, x++) {
        if (real % 2 == 0) {
            move(position.y - 1, x);
            addch(std::to_string(real % 10).at(0));
        }
        if (real % 10 == 0) {
            move(position.y - 2, x);
            addch(std::to_string(real % 100).at(0));
        }
        move(position.y, x);
        addch('-');
        move(position.y + height + 1, x);
        addch('-');
    }
    move(position.y, position.x);
    addch('o');
    move(position.y, position.x + width + 1);
    addch('o');
    move(position.y + height + 1, position.x + width + 1);
    addch('o');
    move(position.y + height + 1, position.x);
    addch('o');
}

void World::RenderSignature() {
    int xSignature = position.x + width + 4;
    int ySignature = position.y - 2;
    move(ySignature, xSignature);
    addstr("Filip Fudala 171560");
}

void World::RenderLegend() {
    int xLegend = position.x + width + 4;
    int yLegend = position.y;
    move(yLegend++, xLegend);
    addstr("\t<=-Animals-=>");
    move(yLegend++, xLegend);
    addstr("S - Sheep\t (Owca)");
    move(yLegend++, xLegend);
    addstr("W - Wolf\t (Wilk)");
    move(yLegend++, xLegend);
    addstr("A - Antelope\t (Antylopa)");
    move(yLegend++, xLegend);
    addstr("F - Fox\t (Lis)");
    move(yLegend++, xLegend);
    addstr("T - Turtle\t (Zolw)");
    move(yLegend++, xLegend);
    addstr("S - Sheep\t (Owca)");
    move(yLegend++, xLegend);
    move(yLegend++, xLegend);
    addstr("\t<=-Plants-=>");
    move(yLegend++, xLegend);
    addstr("h - Hogweed\t (Barszcz Sosnowskiego)");
    move(yLegend++, xLegend);
    addstr("g - Grass\t (Trawa)");
    move(yLegend++, xLegend);
    addstr("s - Sonchus\t (Mlecz)");
    move(yLegend++, xLegend);
    addstr("G - Guarana\t (Guarana)");
    move(yLegend++, xLegend);
    addstr("b - Wolf Berries\t (Wilcze Jagody)");
    move(yLegend++, xLegend);
    move(yLegend++, xLegend);
    addstr("\t<=-Steering-=>");
    move(yLegend++, xLegend);
    addstr("SPACE - Next turn");
    move(yLegend++, xLegend);
    addstr("s - Save current state");
    move(yLegend++, xLegend);
    addstr("j - Scroll down");
    move(yLegend++, xLegend);
    addstr("k - Scroll up");
    move(yLegend, xLegend);
    addstr("q - Quit");
}

Position World::GetRandomNeighbourFreeField(Position pos) {
    std::vector<Position> possibleMoves = GetNeighbourFields(pos);
    possibleMoves.erase(std::remove_if(possibleMoves.begin(), possibleMoves.end
            (), [&](const Position &pos) {
        return GetAtField(pos) != nullptr;
    }), possibleMoves.end());
    if (possibleMoves.size() == 0) {
        throw NoPossibleFieldException();
    }
    Position randomPos = possibleMoves.at(rand() % possibleMoves.size());
    return randomPos;
}

Position World::GetRandomNeighbourField(Position pos) {
    std::vector<Position> possibleMoves = GetNeighbourFields(pos);
    if (possibleMoves.size() == 0) {
        throw NoPossibleFieldException();
    }
    Position randomPos = possibleMoves.at(rand() % possibleMoves.size());
    return randomPos;
}

std::vector<Position> World::GetNeighbourFields(Position pos) {
    std::vector<Position> possibleMoves;
    if (pos.x != 0) {
        possibleMoves.push_back({pos.x - 1, pos.y});
    }
    if (pos.x != width - 1) {
        possibleMoves.push_back({pos.x + 1, pos.y});
    }
    if (pos.y != 0) {
        possibleMoves.push_back({pos.x, pos.y - 1});
    }
    if (pos.y != height - 1) {
        possibleMoves.push_back({pos.x, pos.y + 1});
    }
    // up-left
    if (pos.y != 0 && pos.x != 0) {
        possibleMoves.push_back({pos.x - 1, pos.y - 1});
    }
    // up-right
    if (pos.y != 0 && pos.x != width - 1) {
        possibleMoves.push_back({pos.x + 1, pos.y - 1});
    }
    // down-right
    if (pos.y != height - 1 && pos.x != width - 1) {
        possibleMoves.push_back({pos.x + 1, pos.y + 1});
    }
    // down-left
    if (pos.y != height - 1 && pos.x != 0) {
        possibleMoves.push_back({pos.x - 1, pos.y + 1});
    }
    return possibleMoves;
}

std::string World::Serialize() {
    std::string name("World");
    return name + ',' + std::to_string(width) + ',' + std::to_string(height)
           + ',' + std::to_string(numberOfTurn);
}

void World::Deserialize(std::string data) {

}

void World::SaveToFile() {
    // TODO what if opening file fails
    Log("Type filename to save:");
    Render();
    std::string filename = logger.GetText();
    Log("Are you sure to save current state as " + filename + "? [Y/N]");
    Render();
    int input = getch();
    while (input != 'y' && input != 'Y') {
        if (input == 'n' || input == 'N') {
            Log("Save aborted!", Color::RED);
            return;
        }
        input = getch();
    }
    Log("Saving...", Color::YELLOW);
    Serializator ser;
    ser.OpenToSave(filename);
    ser.WriteToFile(*this);
    manager.WriteToFile(ser);
    ser.Close();
    Log("Saved!", Color::GREEN);
}

void World::LoadFromFile() {
    Log("Type filename to load:");
    Render();
    std::string filename = logger.GetText();
    std::ifstream file;
    // TODO universal

    file.open(filename);

    if(file.good()) {
        
        ResetWorld();

        std::string output;
        Organism *loaded;
        while (getline(file, output)) {
            std::size_t commaPosition = output.find(',');
            std::string type = output.substr(0, commaPosition);
            if (type.compare("World") == 0) {
                Log("Loading World state", Color::YELLOW);
            } else {
                bool isRecognized = false;
                if (type.compare("Fox") == 0) {
                    loaded = new Fox(*this);
                    isRecognized = true;
                } else if (type.compare("Wolf") == 0) {
                    loaded = new Wolf(*this);
                    isRecognized = true;
                } else if (type.compare("Sheep") == 0) {
                    loaded = new Sheep(*this);
                    isRecognized = true;
                } else if (type.compare("Antelope") == 0) {
                    loaded = new Antelope(*this);
                    isRecognized = true;
                } else if (type.compare("Turtle") == 0) {
                    loaded = new Turtle(*this);
                    isRecognized = true;
                } else if (type.compare("Grass") == 0) {
                    loaded = new Grass(*this);
                    isRecognized = true;
                } else if (type.compare("Sonchus") == 0) {
                    loaded = new Sonchus(*this);
                    isRecognized = true;
                } else if (type.compare("Wolf Berry") == 0) {
                    loaded = new WolfBerry(*this);
                    isRecognized = true;
                } else if (type.compare("Guarana") == 0) {
                    loaded = new Guarana(*this);
                    isRecognized = true;
                } else if (type.compare("Hogweed") == 0) {

                    loaded = new Hogweed(*this);
                    isRecognized = true;
                }
                if (isRecognized) {
                    loaded->Deserialize(output);
                    AddOrganism(loaded);
                }
            }
        }
        Log("Loading finished!", Color::GREEN);
    }
    else{
        Log("Couldn't load file \"" + filename + "\"!", Color::RED);
    }
    file.close();
    // TODO refreshing view
}

void World::ResetWorld() {
    manager.RemoveAllOrganisms();
    numberOfTurn = 0;
}
