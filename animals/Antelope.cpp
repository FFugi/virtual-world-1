//
// Created by ffugi on 06.04.18.
//

#include "Antelope.hpp"

void Antelope::Action() {
    // TODO double move
    Animal::Action();
    Animal::Action();
}

Organism *Antelope::Procreate() {
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
    }
    catch (World::NoPossibleFieldException &e){
        return nullptr;
    }
    return new Antelope(newPosition, world);
}

void Antelope::Collision(Organism *other, bool isAttacked) {
    // TODO running away 50% chance
    bool willRunAway = rand() % 100 > 50;
    if(!willRunAway){
        Animal::Collision(other, isAttacked);
        return;
    }
    Position newPosition;
    try{
        newPosition = world.GetRandomNeighbourFreeField(position);
        world.Log(FullName() + " runs away from " + other->FullName(),
                  Logger::YELLOW);
        position = newPosition;
    }
    catch (World::NoPossibleFieldException &e){
        world.Log(FullName() + " couldn't away from " + other->FullName(),
                  Logger::YELLOW);
        Animal::Collision(other, isAttacked);
    }
}

void Antelope::Display(Position beg) const{
    attron(COLOR_PAIR(3));
    Organism::Display(beg);
    attroff(COLOR_PAIR(3));
}
