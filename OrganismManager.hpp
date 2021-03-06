//
// Created by ffugi on 18.04.18.
//

#ifndef VIRTUAL_WORLD_1_ORGANISMMANAGER_HPP
#define VIRTUAL_WORLD_1_ORGANISMMANAGER_HPP

#include <vector>
#include <map>
#include "Position.hpp"
#include "serialization/Serializer.hpp"

class Organism;

class World;

class OrganismManager {
    World &world;
    std::vector<Organism *> organisms;
    std::map<Position, Organism *> map;
    bool wasOrganismAdded;
public:
    OrganismManager(World &world) : world(world), wasOrganismAdded(false) {}

    virtual ~OrganismManager() {
        RemoveAllOrganisms();
    }

    void AddOrganism(Organism *toAdd);

    void RemoveAllOrganisms();

    Organism *GetAtField(Position pos);

    void MoveOrganism(Organism &org, Position newPosition);

    void CleanDeadOrganisms();

    void SortOrganisms();

    void RenderOrganisms(Position startPosition);

    void NextTurn();

    void WriteToFile(Serializer &serializer);

    bool CheckOrganismsCorrectness();
};

#include "Organism.hpp"
#include "World.hpp"

#endif //VIRTUAL_WORLD_1_ORGANISMMANAGER_HPP
