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
#include "serialization/Parser.hpp"
#include "animals/Human.hpp"
#include "OrganismFactory.hpp"

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
    return input == ' ' ? Command::NEXT_TURN :
           input == 'q' ? Command::EXIT :
           input == 's' ? Command::SAVE :
           input == 'l' ? Command::LOAD :
           input == 'k' ? Command::SCROLL_UP :
           input == 'j' ? Command::SCROLL_DOWN :
           Command::ERROR;
}

World::Command World::NextTurn() {
    logger.Log("Enter command!");
    Render();
    Command cmd = GetInput();
    while (cmd != Command::NEXT_TURN) {
        switch (cmd) {
            case Command::SAVE:
                SaveToFile();
                break;
            case Command::LOAD:
                LoadFromFile();
                break;
            case Command::SCROLL_UP:
                logger.ScrollUp();
                break;
            case Command::SCROLL_DOWN:
                logger.ScrollDown();
                break;
            case Command::EXIT:
                return cmd;
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
        addch(ACS_VLINE);
        move(y, position.x + width + 1);
        addch(ACS_VLINE);
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
        addch(ACS_HLINE);
        move(position.y + height + 1, x);
        addch(ACS_HLINE);
    }
    move(position.y, position.x);
    addch(ACS_ULCORNER);
    move(position.y, position.x + width + 1);
    addch(ACS_URCORNER);
    move(position.y + height + 1, position.x + width + 1);
    addch(ACS_LRCORNER);
    move(position.y + height + 1, position.x);
    addch(ACS_LLCORNER);
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
    return possibleMoves;
}

std::string World::Serialize() {
    std::string name("World");
    return name + ',' + std::to_string(width) + ',' + std::to_string(height)
           + ',' + std::to_string(numberOfTurn);
}

void World::Deserialize(std::string data) {
    /*
     * Format
     * width,height,turn
     */
    Parser parser(data);
    width = std::atoi(parser.GetPartOfString(1).c_str());
    height = std::atoi(parser.GetPartOfString(2).c_str());
    numberOfTurn = std::atoi(parser.GetPartOfString(3).c_str());
}

void World::SaveToFile() {
    Log("Type filename to save:");
    Render();
    std::string filename = logger.GetText();
    int willSave = logger.GetConfirmation(
            "Are you sure to save current state as " + filename + "?");
    Render();
    if (!willSave) {
        Log("Save aborted!", Color::RED);
        return;
    }
    Log("Saving...", Color::CYAN);
    Serializer ser;
    ser.OpenToSave(filename);
    if (ser.IsOpenSuccessful()) {
        ser.WriteToFile(*this);
        manager.WriteToFile(ser);
        ser.Close();
        Log("Saved!", Color::GREEN);
    } else {
        Log("File not saved, something went wrong!", Color::RED);
    }
}

void World::LoadFromFile() {
    Log("Type filename to load:");
    Render();
    std::string filename = logger.GetText();
    std::ifstream file;

    file.open(filename);

    if (file.good()) {

        int willLoad = logger.GetConfirmation("Are you sure to open "
                                              + filename + "?");
        Render();
        if (!willLoad) {
            Log("Load aborted!", Color::RED);
            return;
        }

        Log("Starting loading...", Color::CYAN);

        ResetWorld();

        std::string output;
        Organism *loaded;
        OrganismFactory factory;
        while (getline(file, output)) {

            Parser parser(output);
            std::string type = parser.GetPartOfString(0);
            if (type == "World") {
                Log("Loading World state", Color::WHITE);
                Deserialize(output);
            } else {
                loaded = factory.GetOrganism(type, *this);

                if (loaded != nullptr) {
                    loaded->Deserialize(output);
                    AddOrganism(loaded);
                }
            }
        }
        Log("Loading finished!", Color::GREEN);
    } else {
        Log("Couldn't open file \"" + filename + "\"!", Color::RED);
    }
    file.close();
    // TODO refreshing view
}

void World::ResetWorld() {
    manager.RemoveAllOrganisms();
    numberOfTurn = 0;
}

