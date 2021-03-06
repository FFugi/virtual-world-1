//
// Created by ffugi on 06.04.18.
//

#include "WolfBerry.hpp"

void WolfBerry::Collision(Organism *other, bool isAttacked) {
    // TODO is strength important?
    Kill(other);
    other->Kill(this, "from inside");
    // TODO is it ok?
}

Organism *WolfBerry::GetNewOrganism() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new WolfBerry(newPosition, world);
}
