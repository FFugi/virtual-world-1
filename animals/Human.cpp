//
// Created by ffugi on 21.04.18.
//

#include "Human.hpp"

void Human::Action() {
    world.Log("Choose direction to move!");
    world.Render();

    int command = 0;
    bool confirm = false;
    Position newPosition;
    while (!confirm) {
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
            default:
                world.Log("Unknown command");
                break;
        }
        confirm = true;
        bool isMovePossible = IsMovePossible(newPosition);
        if (isMovePossible) {
            Organism *neighbour = world.GetAtField(newPosition);
            if (neighbour != nullptr) {
                neighbour->Collision(this, true);
            }
            world.MoveOrganism(this, newPosition);
        } else {
            world.Log("this move is impossiblu!!!!");
            confirm = false;
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

// TODO Collision!!

Organism *Human::Procreate() {
    world.Log("Human cannot procreate!");
    return nullptr;
}
