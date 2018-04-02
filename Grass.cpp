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
