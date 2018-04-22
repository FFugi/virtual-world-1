//
// Created by ffugi on 26.03.18.
//

#include "Organism.hpp"
#include "serialization/Parser.hpp"


void Organism::Display(Position beg) const {
    move(beg.y + position.y, beg.x + position.x);
    attron(COLOR_PAIR(static_cast<int>(displayedColor)));
    addch(symbol | A_BOLD);
    attroff(COLOR_PAIR(static_cast<int>(displayedColor)));
}

bool Organism::CompareInitiative(Organism *first, Organism *second) {
    return first->initiative == second->initiative ? first->age > second->age :
           first->initiative > second->initiative;
}

std::string Organism::FullName() const {
    return name + " a:" + std::to_string(age) + " i:" +
           std::to_string(initiative) + " s:" + std::to_string(strength) +
           " (" + std::to_string(position.x) + "," +
           std::to_string(position.y) + ")";
}

void Organism::IncrementAge() {
    age++;
}

int Organism::GetStrength() const {
    return strength;
}

Position Organism::GetPosition() const {
    return position;
}

void Organism::Kill(Organism *attacker) {
    Kill(attacker, "");
    isAlive = false;
}

void Organism::Kill(Organism *attacker, std::string comment) {
    world.Log(
            attacker->FullName() + " kills " + FullName() + " " + comment,
            Color::RED);
    isAlive = false;
}

bool Organism::IsAlive() const {
    return isAlive;
}

void Organism::SetPosition(Position position) {
    this->position = position;
}

void Organism::ModifyStrength(int value) {
    strength += value;
}

std::string Organism::Serialize() {
    return name + ',' + std::to_string(age) + ',' +
           std::to_string(initiative) + ',' + std::to_string(strength) + ',' +
           std::to_string(position.x) + ',' + std::to_string(position.y);
}

void Organism::Deserialize(std::string data) {
    /*
     * Format
     * age,initiative, strength, x, y
     */
    // TODO not found in string
    Parser parser(data);
    std::string buffer = parser.GetPartOfString(1);
    if (!buffer.empty()) {
        age = std::atoi(buffer.c_str());
    }
    buffer = parser.GetPartOfString(2);
    if (!buffer.empty()) {
        initiative = std::atoi(parser.GetPartOfString(2).c_str());
    }
    buffer = parser.GetPartOfString(3);
    if (!buffer.empty()) {
        strength = std::atoi(parser.GetPartOfString(3).c_str());
    }
    buffer = parser.GetPartOfString(4);
    if (!buffer.empty()) {
        position.x = std::atoi(parser.GetPartOfString(4).c_str());
    }
    buffer = parser.GetPartOfString(5);
    if (!buffer.empty()) {
        position.y = std::atoi(parser.GetPartOfString(5).c_str());
    }

    world.Log("Loaded " + FullName());
}
