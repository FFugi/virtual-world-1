//
// Created by ffugi on 06.04.18.
//

#include "Hogweed.hpp"

void Hogweed::Action() {
    std::vector<Position> positions = world.GetNeighbourFields(position);
    std::vector<Organism*> neighbours;
    for(auto pos : positions){
        Organism * neighbour = world.GetAtField(pos);
        if(neighbour != nullptr && dynamic_cast<Animal*>(neighbour)){
            neighbour->Kill(this);
        }
    }
    Plant::Action();
}

void Hogweed::Collision(Organism *other, bool isAttacked) {
    // TODO
    Plant::Collision(other, isAttacked);
}

Organism *Hogweed::Procreate() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Hogweed(newPosition, world);
}

void Hogweed::Display(Position beg) const {
    attron(COLOR_PAIR(1));
    Organism::Display(beg);
    attroff(COLOR_PAIR(1));
}
