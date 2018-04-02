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
    std::vector<Position> possibleFields = world.GetPossibleEmptyFields(position);
    if(possibleFields.size() == 0){
        return;
    }
    Position newPosition = possibleFields.at(rand() % possibleFields.size());
    if(world.GetAtField(newPosition) != nullptr){
        return;
    }
    if (dynamic_cast<Grass *>(this)) {
        world.AddOrganism(new Grass(newPosition, world));
    }
}
