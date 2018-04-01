//
// Created by ffugi on 27.03.18.
//

#ifndef VIRTUAL_WORLD_1_SHEEP_HPP
#define VIRTUAL_WORLD_1_SHEEP_HPP

#include "Animal.hpp"

class Sheep : public Animal{
public:

public:

    Sheep(Position position, World &world);

    void Collision() override;

    void Action() override;



};


#endif //VIRTUAL_WORLD_1_SHEEP_HPP
