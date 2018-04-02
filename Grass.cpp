//
// Created by ffugi on 01.04.18.
//

#include "Grass.hpp"

Grass::Grass(Position position, World &world) : Plant (position, world,
                                                          strength, 'g',
                                                       "Grass") {}


void Grass::Action() {
    Plant::Action();
}


Organism *Grass::Procrastinate() {
    std::vector<Position> possibleFields= world.GetPossibleEmptyFields
            (position);
    if(possibleFields.size() == 0){
        return nullptr;
    }
    Position newPosition = possibleFields.at(rand() % possibleFields.size());
    world.Log(
            "Grass at " + std::to_string(position.x) + ", " + std::to_string
                    (position.y) + " generates new grass at: " +
            std::to_string(newPosition.x) + ", " +
            std::to_string(newPosition.y));
    return new Grass(newPosition, world);
}
