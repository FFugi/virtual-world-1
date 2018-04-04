//
// Created by ffugi on 01.04.18.
//

#ifndef VIRTUAL_WORLD_1_PLANT_HPP
#define VIRTUAL_WORLD_1_PLANT_HPP

#include <cstdlib>
#include "Organism.hpp"

class Plant: public Organism {
protected:
    short propabilityOfProcrastination;
public:
    Plant(Position position, World &world, int strength,
          char symbol, std::string name);

    void Collision(Organism *other, bool isAttacked) override;

    void Action() override;

};

#include "World.hpp"

#endif //VIRTUAL_WORLD_1_PLANT_HPP
