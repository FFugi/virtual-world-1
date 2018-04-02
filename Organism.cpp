//
// Created by ffugi on 26.03.18.
//

#include "Organism.hpp"


void Organism::Display(Position beg) const {
    move(beg.y + position.y, beg.x + position.x);
    addch(symbol);
}

bool Organism::CompareInitiative(Organism &first, Organism &second) {
    return first.initiative == second.initiative ? first.age < second.age :
           first.initiative < second.initiative;
}

int Organism::GetStrength() const {
    return strength;
}

Position Organism::GetPosition() const {
    return position;
}

void Organism::Kill() {
    isAlive = false;
}

bool Organism::IsAlive() const {
    return isAlive;
}

void Organism::SetPosition(Position position) {
    this->position = position;
}
