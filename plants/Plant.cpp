//
// Created by ffugi on 01.04.18.
//

#include "Plant.hpp"
#include "Grass.hpp"



void Plant::Collision(Organism *other, bool isAttacked) {
    if (other->GetStrength() > strength) {
        Kill(other);
        world.MoveOrganism(other, position);
    } else {
        other->Kill(this);
    }
}

void Plant::Action() {
    bool willProcastrinate = (rand() % 100 < propabilityOfProcrastination);
    if (!willProcastrinate) {
        return;
    }

    Organism *newOrganism = GetNewOrganism();
    if (newOrganism == nullptr) {
        //world.Log("No place for new" + name);
        return;
    }
    Position newPosition = newOrganism->GetPosition();
    world.Log(FullName() +" generates new " + name + " (" +
              std::to_string(newPosition.x) + "," +
              std::to_string(newPosition.y) + ")", Color::GREEN);
    world.AddOrganism(newOrganism);
}
