//
// Created by ffugi on 18.04.18.
//

#ifndef VIRTUAL_WORLD_1_ORGANISMMANAGER_HPP
#define VIRTUAL_WORLD_1_ORGANISMMANAGER_HPP


#include "Organism.hpp"
#include <unordered_map>

class OrganismManager {
    std::vector<Organism*> organisms;
    std::unordered_map<Position, Organism*> map;

    OrganismManager() {}
    void RemoveAllOrganisms();
    void AddOrganism();
    Organism * GetAtField();
    void MoveOrganism();
    void CleadDeadOrganisms();

};


#endif //VIRTUAL_WORLD_1_ORGANISMMANAGER_HPP
