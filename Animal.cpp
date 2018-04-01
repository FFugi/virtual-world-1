//
// Created by ffugi on 01.04.18.
//

#include "Animal.hpp"

Animal::Animal(Position position, World &world, int initiative, int strength,
               char symbol) : Organism(position, world, initiative, strength,
                                       symbol) {}


void Animal::Collision() {
    // TODO procrastination
}

void Animal::Action() {
    // TODO random move
    std::vector<Position> possibleFields= world.GetPossibleFields(position);
    position = possibleFields.at( rand() % possibleFields.size() );
}
