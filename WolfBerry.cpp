//
// Created by ffugi on 06.04.18.
//

#include "WolfBerry.hpp"

void WolfBerry::Collision(Organism *other, bool isAttacked) {
    // TODO is strength important?
    world.Log(other->FullName() + " attacks " + FullName() + " and gets killed"
                                                             ,2);
    other->Kill();
}

Organism *WolfBerry::Procreate() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new WolfBerry(newPosition, world);
}

void WolfBerry::Display(Position beg) const {
    attron(COLOR_PAIR(5));
    Organism::Display(beg);
    attroff(COLOR_PAIR(5));
}
