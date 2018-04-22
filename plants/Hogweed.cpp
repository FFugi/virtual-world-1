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
    Kill(other);
    world.MoveOrganism(other, position);
    other->Kill(this, "from inside");
}

Organism *Hogweed::GetNewOrganism() {
    Position newPosition;
    try {
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e) {
        return nullptr;
    }
    return new Hogweed(newPosition, world);
}
