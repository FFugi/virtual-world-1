//
// Created by ffugi on 21.04.18.
//

#include "Human.hpp"

void Human::Action() {
    world.Log("Choose action for your human!");
    if(IsPowerActive()){
        world.Log("Immortality is active!", Color::CYAN);
    } else if(IsPowerActivable()){
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
                world.Log("Unknown command");
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
                world.Log("this move is impossible!", Color::RED);
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
    if (other->GetStrength() >= strength) {
        try {
            Position newPosition = world.GetRandomNeighbourFreeField(position);
            world.MoveOrganism(this, newPosition);
        } catch (World::NoPossibleFieldException &e) {
            world.Log(FullName() + " resists attack from " + other->FullName(),
                      Color::YELLOW);
        }
    }
}

Organism *Human::Procreate() {
    world.Log("Human cannot procreate!");
    return nullptr;
}

bool Human::IsPowerActive() {
    return age - ageWhenPowerWasUsed < 5;
}

bool Human::IsPowerActivable() {
    return age - ageWhenPowerWasUsed >= 10;
}
