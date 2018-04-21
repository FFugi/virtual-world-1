//
// Created by ffugi on 26.03.18.
//

#include "Organism.hpp"


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
    world.Log(attacker->FullName() + " kills " + FullName(), Color::RED);
    isAlive = false;
}

void Organism::Kill(Organism *attacker, std::string comment) {
    world.Log(
            attacker->FullName() + " kills " + FullName() + " " + comment,
            Color::RED );
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
    //world.Log(data);
    std::size_t comma = data.find(',');
    std::string rest = data.substr(comma+1);
    comma = rest.find(',');
    age = std::stoi(rest.substr(0, comma));
    rest = rest.substr((comma+1));
    comma = rest.find(',');
    initiative = std::stoi(rest.substr(0, comma));
    rest = rest.substr((comma+1));
    comma = rest.find(',');
    strength = std::stoi(rest.substr(0, comma));
    rest = rest.substr((comma+1));
    comma = rest.find(',');
    position.x = std::stoi(rest.substr(0, comma));
    rest = rest.substr((comma+1));
    comma = rest.find(',');
    position.y = std::stoi(rest.substr(0, comma));

    world.Log("Loaded "+FullName());
}
