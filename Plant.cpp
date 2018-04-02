//
// Created by ffugi on 01.04.18.
//

#include "Plant.hpp"
#include "Grass.hpp"

Plant::Plant(Position position, World &world, int strength, char symbol,
             std::string name)
        : Organism(position, world, 0, strength,
                   symbol, name), propabilityOfProcrastination(3) {}

void Plant::Collision(Organism * other) {

}

void Plant::Action() {
    // TODO propability
    bool willProcastrinate = (
            rand() % 100 < propabilityOfProcrastination);
    if (!willProcastrinate) {
        return;
    }

    Organism * newOrganism = Procrastinate();
    if(newOrganism == nullptr){
        // TODO log
        return;
    }
    world.AddOrganism(newOrganism);
}
