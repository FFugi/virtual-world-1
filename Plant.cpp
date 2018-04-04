//
// Created by ffugi on 01.04.18.
//

#include "Plant.hpp"
#include "Grass.hpp"

Plant::Plant(Position position, World &world, int strength, char symbol,
             std::string name)
        : Organism(position, world, 0, strength,
                   symbol, name), propabilityOfProcrastination(3) {}

void Plant::Collision(Organism *other) {
    world.Log("collision! of " + FullName()+ " and " + other->FullName()+ " at " + " " +
              std::to_string(position.x) + " " + std::to_string(position.y));
    // TODO next
    if (!isAlive) {
        // TODO ok?
        world.Log("wtf?? :o");
        return;
    }
    if (other->GetStrength() > strength) {
        world.Log(other->FullName()+ " kills " + FullName(), 2);
        Kill();
        other->SetPosition(position);
    } else {
        world.Log(FullName()+ " kills " + other->FullName(), 2);
        other->Kill();
    }
}

void Plant::Action() {
    // TODO propability
    bool willProcastrinate = (
            rand() % 100 < propabilityOfProcrastination);
    if (!willProcastrinate) {
        return;
    }

    Organism *newOrganism = Procreate();
    if (newOrganism == nullptr) {
        // TODO log
        world.Log("No place for new" + name);
        return;
    }
    Position newPosition = newOrganism->GetPosition();
    world.Log(FullName()+ " at " + std::to_string(position.x) + ", " + std::to_string
            (position.y) + " generates new " + name + " at: " + std::to_string
                      (newPosition.x) + ", " + std::to_string(newPosition.y),
              1);
    world.AddOrganism(newOrganism);
}
