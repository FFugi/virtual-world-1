//
// Created by ffugi on 22.04.18.
//

#ifndef VIRTUAL_WORLD_1_ANIMALFACTORY_HPP
#define VIRTUAL_WORLD_1_ANIMALFACTORY_HPP

#include "Organism.hpp"

class OrganismFactory {
public:
    OrganismFactory(){}

    Organism *GetOrganism(std::string name, World &world);

    Organism *GetOrganism(std::string name, Position position, World &world);

};


#endif //VIRTUAL_WORLD_1_ANIMALFACTORY_HPP
