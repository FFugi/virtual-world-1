//
// Created by ffugi on 06.04.18.
//

#ifndef VIRTUAL_WORLD_1_WOLFBERRY_HPP
#define VIRTUAL_WORLD_1_WOLFBERRY_HPP


#include "Plant.hpp"

class WolfBerry : public Plant {

public:
    WolfBerry(Position position, World &world) :
            Plant(position, world, 99, 'b', "Wolf Berry", Color::CYAN) {};

    WolfBerry(World &world) : Plant({0,0}, world, 99, 'b', "Wolf Berry",
                                    Color::CYAN) {};

    void Collision(Organism *other, bool isAttacked) override ;

    Organism *Procreate() override;
};


#endif //VIRTUAL_WORLD_1_WOLFBERRY_HPP
