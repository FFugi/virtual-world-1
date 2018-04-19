//
// Created by ffugi on 18.04.18.
//

#include "OrganismManager.hpp"

void OrganismManager::AddOrganism(Organism * toAdd) {
    organisms.push_back(toAdd);
    map[toAdd->GetPosition()] = toAdd;
    // TODO Debug
    for(auto org : map){
        world.Log(org.second->FullName() + " (" + std::to_string(org.first.x) +
                  +", " + std::to_string(org.first.y) + ")");
    }
    world.Log("---");
}

void OrganismManager::RemoveAllOrganisms() {
    for(auto org: organisms){
        delete org;
    }
    organisms.clear();
    map.clear();
}

Organism *OrganismManager::GetAtField(Position pos) {
    auto result = map.find(pos);
    if(result != map.end()){
        return result->second;
    }
    return nullptr;
}

void OrganismManager::MoveOrganism(Organism &org, Position newPosition) {
    auto handler = map.extract(org.GetPosition());
    handler.key() = newPosition;
    map.insert(std::move(handler));
    org.SetPosition(newPosition);
}

void OrganismManager::CleadDeadOrganisms() {
    std::vector<Organism*> toDelete;
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
        delete org;
    }
}

void OrganismManager::SortOrganisms() {
    std::sort(organisms.begin(), organisms.end(), Organism::CompareInitiative);
}
