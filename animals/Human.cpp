//
// Created by ffugi on 21.04.18.
//

#include "Human.hpp"
#include "../serialization/Parser.hpp"

void Human::Action() {
    world.Log("Choose action for your human!", Color::YELLOW);
    if (IsPowerActive()) {
        world.Log("Immortality is active!", Color::CYAN);
    } else if (IsPowerActivable()) {
        world.Log("Immortality can be activated.", Color::GREEN);
    } else {
        world.Log("Immortality can't be activated.", Color::MAGENTA);
    }
    world.Render();

    int command = 0;
    bool finish = false;
    Position newPosition = position;
    while (!finish) {
        finish = true;
        command = getch();
        switch (command) {
            case KEY_LEFT:
                newPosition = {position.x - 1, position.y};
                break;
            case KEY_RIGHT:
                newPosition = {position.x + 1, position.y};
                break;
            case KEY_UP:
                newPosition = {position.x, position.y - 1};
                break;
            case KEY_DOWN:
                newPosition = {position.x, position.y + 1};
                break;
            case 'i':
                if (IsPowerActivable()) {
                    ageWhenPowerWasUsed = age;
                    world.Log("Immortality activated!", Color::CYAN);
                    finish = false;
                }
                break;
            default:
                world.Log("Your human doesn't recognize this command!",
                          Color::YELLOW);
                break;
        }
        bool isMovePossible = IsMovePossible(newPosition);
        if (isMovePossible) {
            Organism *neighbour = world.GetAtField(newPosition);
            if (neighbour != nullptr) {
                if (neighbour->GetStrength() > strength
                    && IsPowerActive()) {
                    world.Log("Human tried to attack " + neighbour->FullName()
                              + " but survived due to Immortality!",
                              Color::YELLOW);
                    finish = true;
                } else {
                    neighbour->Collision(this, true);
                }
            } else {
                world.MoveOrganism(this, newPosition);
            }
        } else {
            if (!(newPosition == position)) {
                world.Log("This move is impossible!", Color::RED);
            }
            finish = false;
        }
        world.Render();
    }

}

bool Human::IsMovePossible(Position newPosition) {
    auto possibleMoves = world.GetNeighbourFields(position);
    for (auto pos : possibleMoves) {
        if (pos == newPosition) {
            return true;
        }
    }
    return false;
}

// Immortality
void Human::Collision(Organism *other, bool isAttacked) {
    if (IsPowerActive() && other->GetStrength() >= strength) {
        try {
            Position newPosition = world.GetRandomNeighbourFreeField(position);
            world.MoveOrganism(this, newPosition);
        } catch (World::NoPossibleFieldException &e) {
            LogResistedAttack(other);
        }
    } else {
        Animal::Collision(other, isAttacked);
    }
}

void Human::LogResistedAttack(const Organism *other) const {
    world.Log(FullName() + " resists attack from " + other->FullName()
              + " due to immortality", Color::YELLOW);
}

Organism *Human::GetNewOrganism() {
    world.Log("Human cannot procreate!");
    return nullptr;
}

bool Human::IsPowerActive() {
    return age - ageWhenPowerWasUsed < 5;
}

bool Human::IsPowerActivable() {
    return age - ageWhenPowerWasUsed >= 10;
}

void Human::Kill(Organism *attacker) {
    if (!IsPowerActive()) {
        Organism::Kill(attacker);
        return;
    }
    LogResistedAttack(attacker);
}

void Human::Kill(Organism *attacker, std::string comment) {
    if (!IsPowerActive()) {
        Organism::Kill(attacker, comment);
        return;
    }
    LogResistedAttack(attacker);
}

std::string Human::Serialize() const {
    return Organism::Serialize() + ',' + std::to_string(ageWhenPowerWasUsed);
}

void Human::Deserialize(std::string data) {
    Organism::Deserialize(data);
    Parser parser(data);
    std::string buffer = parser.GetPartOfString(6).c_str();
    if (!buffer.empty()) {
        ageWhenPowerWasUsed = std::atoi(buffer.c_str());
    }
}

