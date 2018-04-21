//
// Created by ffugi on 06.04.18.
//

#include "Guarana.hpp"

void Guarana::Action() {
        Plant::Action();
}

Organism *Guarana::Procreate() {
    // TODO move try-catch up to organism
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch(World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Guarana(newPosition, world);
}

void Guarana::Collision(Organism *other, bool isAttacked) {
    Plant::Collision(other, isAttacked);
    world.Log(FullName() + " increments strength of " + other->FullName() +
              " to "+ std::to_string(other->GetStrength() + 3), Color::YELLOW);
    other->ModifyStrength(3);
}
