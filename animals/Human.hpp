//
// Created by ffugi on 21.04.18.
//

#ifndef VIRTUAL_WORLD_1_HUMAN_HPP
#define VIRTUAL_WORLD_1_HUMAN_HPP


#include "Animal.hpp"

class Human : public Animal {
private:
    int ageWhenPowerWasUsed;

    bool IsMovePossible(Position newPosition);

    bool IsPowerActive();

    bool IsPowerActivable();

public:
    Human(Position position, World &world) : Animal(position, world, 4,
                                                    5, 'H', "Human",
                                                    Color::YELLOW),
                                             ageWhenPowerWasUsed(-10) {}

    Human(World &world) : Animal({0, 0}, world, 4, 5, 'H', "Human",
                                 Color::YELLOW) {}

    void Action() override;

    void Collision(Organism *other, bool isAttacked) override;

    Organism *GetNewOrganism() override;

    void Kill(Organism *attacker) override;

    void Kill(Organism *attacker, std::string comment) override;

    std::string Serialize() override;

    void Deserialize(std::string data) override;
};


#endif //VIRTUAL_WORLD_1_HUMAN_HPP
