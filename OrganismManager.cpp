//
// Created by ffugi on 18.04.18.
//

#include "OrganismManager.hpp"
#include "plants/Sonchus.hpp"

void OrganismManager::AddOrganism(Organism *toAdd) {
    organisms.push_back(toAdd);
    map[toAdd->GetPosition()] = toAdd;
    wasOrganismAdded = true;
}

void OrganismManager::RemoveAllOrganisms() {
    for (auto org: organisms) {
        delete org;
    }
    organisms.clear();
    map.clear();
}

Organism *OrganismManager::GetAtField(Position pos) {
    auto result = map.find(pos);
    if (result != map.end()) {
        return result->second;
    }
    return nullptr;
}

void OrganismManager::MoveOrganism(Organism &org, Position newPosition) {
    map.erase(org.GetPosition());
    org.SetPosition(newPosition);
    map[org.GetPosition()] = &org;
}

void OrganismManager::CleanDeadOrganisms() {
    std::vector<Organism *> toDelete;
    for (std::size_t i = 0; i < organisms.size(); i++) {
        if (!organisms.at(i)->IsAlive()) {
            toDelete.push_back(organisms.at(i));
        }
    }
    organisms.erase(std::remove_if(organisms.begin(), organisms.end(),
                                   [](const Organism *org) {
                                       return !org->IsAlive();
                                   }), organisms.end());
    for (auto org : toDelete) {
        // Check if overwritten
        if (map[org->GetPosition()] != nullptr
            && !map[org->GetPosition()]->IsAlive()) {
            map.erase(org->GetPosition());
        }
        delete org;
    }
}

void OrganismManager::SortOrganisms() {
    std::sort(organisms.begin(), organisms.end(), Organism::CompareInitiative);
}

void OrganismManager::RenderOrganisms(Position startPosition) {
    for (auto org: organisms) {
        if (org->IsAlive()) {
            org->Display({startPosition.x + 1, startPosition.y + 1});
        }
    }
}

void OrganismManager::NextTurn() {
    if (wasOrganismAdded) {
        SortOrganisms();
        wasOrganismAdded = false;
    }
    std::size_t iterations = organisms.size();
    for (std::size_t i = 0; i < iterations; i++) {
        if (organisms.at(i)->IsAlive()) {
            organisms.at(i)->Action();
        }
    }
    for (auto org : organisms) {
        org->IncrementAge();
    }
    CleanDeadOrganisms();
}

void OrganismManager::WriteToFile(Serializer &serializer) {
    for (auto org : organisms) {
        serializer.WriteToFile(*org);
    }
}
