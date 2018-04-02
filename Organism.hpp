//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_ORGANISM_HPP
#define VIRTUAL_WORLD_1_ORGANISM_HPP

#include <ncurses.h>
#include <cstddef>
#include <string>
#include "structures.hpp"

class World;

class Organism {
protected:
    Position position;
    World &world;
    int initiative;
    int strength;
    char symbol;
    int age;
    bool isAlive;
public:
    const std::string name;

public:
    Organism(Position position, World &world, int initiative, int strength, char
    symbol, std::string name) :
            position(position), world(world), initiative(initiative),
            strength(strength), symbol(symbol), age(0),isAlive(true), name
                    (name)
            {}

    virtual void Collision(Organism * other) = 0;

    virtual void Display(Position beg) const ;

    virtual void Action() = 0;

    static bool CompareInitiative(Organism &first, Organism &second);

    virtual Position GetPosition() const;

    virtual Organism *Procrastinate() = 0;

    virtual void Kill();

    virtual bool IsAlive() const;

    virtual int GetStrength() const;

    virtual void SetPosition(Position position);
};


#endif //VIRTUAL_WORLD_1_ORGANISM_HPP
