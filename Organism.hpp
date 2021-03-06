//
// Created by ffugi on 26.03.18.
//
#ifndef VIRTUAL_WORLD_1_ORGANISM_HPP
#define VIRTUAL_WORLD_1_ORGANISM_HPP

#include <ncurses.h>
#include <cstddef>
#include <string>
#include "Position.hpp"
#include "serialization/Serializable.hpp"
#include "Logger.hpp"

class World;

class Organism : public Serializable {
protected:
    Position position;
    World &world;
    int initiative;
    int strength;
    char symbol;
    int age;
    bool isAlive;
    const std::string name;
    Color displayedColor;

public:
    Organism(Position position, World &world, int initiative, int strength, char
    symbol, std::string name, Color color) :
            position(position), world(world), initiative(initiative),
            strength(strength), symbol(symbol), age(0), isAlive(true),
            name(name), displayedColor(color) {}

    // TODO check = default
    virtual ~Organism() = default;

    virtual void Collision(Organism *other, bool isAttacked) = 0;

    virtual void Display(Position beg) const;

    virtual void Action() = 0;

    static bool CompareInitiative(Organism *first, Organism *second);

    virtual Position GetPosition() const;

    virtual Organism *GetNewOrganism() = 0;

    virtual void Kill(Organism *attacker);

    virtual void Kill(Organism *attacker, std::string comment);

    virtual bool IsAlive() const;

    virtual int GetStrength() const;

    virtual void SetPosition(Position positoion);

    virtual std::string FullName() const;

    virtual void IncrementAge();

    virtual void ModifyStrength(int value);

    std::string Serialize() const override;

    void Deserialize(std::string data) override;
};

#include "World.hpp"

#endif //VIRTUAL_WORLD_1_ORGANISM_HPP
