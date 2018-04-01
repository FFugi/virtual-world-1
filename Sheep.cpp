//
// Created by ffugi on 27.03.18.
//

#include "Sheep.hpp"

Sheep::Sheep(Position position, World &world) : Animal(position, world, 4,
                                                  4, 'S') {}


void Sheep::Collision() {

}

void Sheep::Action() {
    Animal::Action();
}

