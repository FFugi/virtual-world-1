//
// Created by ffugi on 01.04.18.
//

#include "Plant.hpp"
#include "Grass.hpp"

Plant::Plant(Position position, World &world, int strength, char symbol)
        : Organism(position, world, 0, strength,
                   symbol), propabilityOfProcrastination(10) {}

void Plant::Collision() {

}

void Plant::Action() {
    // TODO propability
    bool willProcastrinate =(
            rand() % 100 < propabilityOfProcrastination);
    if (!willProcastrinate) {
        return;
    }
  //  std::vector<Position> possibleFields = world.GetPossibleFields(position);
  //  Position newPosition = possibleFields.at(rand() % possibleFields.size());
    if (dynamic_cast<Grass *>(this)) {
        world.Log("New grass");
        //world.AddOrganism(new Grass(newPosition, world));
    }
}
