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
    world.Log("collision! of " + name + " and " + other->name + " at " + " " +
              std::to_string(position.x) + " " + std::to_string(position.y));
    // TODO next
    if (!isAlive) {
        // TODO ok?
        world.Log("wtf?? :o");
        return;
    }
    if (other->GetStrength() > strength) {
        world.Log(other->name + " kills " + name);
        Kill();
        other->SetPosition(position);
    } else {
        world.Log(name + " kills " + other->name);
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

    Organism *newOrganism = Procrastinate();
    if (newOrganism == nullptr) {
        // TODO log
        world.Log("Plant is great wtf?? :o");
        return;
    }
    Position newPosition = newOrganism->GetPosition();
    world.Log(name + " at " + std::to_string(position.x) + ", " + std::to_string
            (position.y) + " generates new " + name + " at: " + std::to_string
                      (newPosition.x) + ", " + std::to_string(newPosition.y));
    world.AddOrganism(newOrganism);
}
