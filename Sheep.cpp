//
// Created by ffugi on 27.03.18.
//

#include "Sheep.hpp"

Sheep::Sheep(Position position, World &world) : Animal(position, world, 4,
                                                  4, 'S', "Sheep") {}



void Sheep::Action() {
    Animal::Action();
}


Organism *Sheep::Procrastinate() {
    std::vector<Position> possibleFields= world.GetPossibleEmptyFields
            (position);
    if(possibleFields.size() == 0){
        return nullptr;
    }
    Position newPosition = possibleFields.at(rand() % possibleFields.size());
    return new Sheep(newPosition, world);
}
