//
// Created by ffugi on 06.04.18.
//

#ifndef VIRTUAL_WORLD_1_GUARANA_HPP
#define VIRTUAL_WORLD_1_GUARANA_HPP


#include "Plant.hpp"

class Guarana : public Plant {
public:
    Guarana(Position position, World &world) :
            Plant(position, world, 0, 'G', "Guarana", Color::MAGENTA) {};

    Guarana(World &world) : Plant({0,0}, world, 0, 'G', "Guarana",
                                  Color::MAGENTA) {};

    void Action() override;

    void Collision(Organism *other, bool isAttacked) override ;

    Organism *GetNewOrganism() override;
};


#endif //VIRTUAL_WORLD_1_GUARANA_HPP
