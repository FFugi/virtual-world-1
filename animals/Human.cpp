//
// Created by ffugi on 21.04.18.
//

#include "Human.hpp"

void Human::Action() {
    world.Log("Choose direction to move!");
    world.Render();

    short vertical = 0;
    short horizontal = 0;
    std::string horizontalStr;
    std::string verticalStr;
    bool confirm = false;
    int command = 0;

    auto possibleMoves = world.GetNeighbourFields(position);
    while (!confirm) {
        command = getch();
        switch (command) {
            case KEY_LEFT:
                horizontal--;
                break;
            case KEY_RIGHT:
                horizontal++;
                break;
            case KEY_UP:
                vertical--;
                break;
            case KEY_DOWN:
                vertical++;
                break;
            case 10:
                confirm = true;
                world.Log("Confirmed!");
                break;
            default:
                world.Log("Unknown command");
                break;
        }

        if(vertical < 0){
            vertical = -1;
        } else if(vertical > 0){
            vertical = 1;
        }
        if(horizontal < 0){
            horizontal = -1;
        } else if(horizontal > 0){
            horizontal = 1;
        }
        if(confirm){
            Position newPosition = {position.x + horizontal, position.y + vertical};
            bool isMovePossible = false;
            for(auto pos : possibleMoves){
                if(pos == newPosition){
                    isMovePossible = true;
                }
            }
            if (isMovePossible) {
                Organism * neighbour =world.GetAtField(newPosition);
                if(neighbour != nullptr){
                    neighbour->Collision(this, true);
                }
                world.MoveOrganism(this, newPosition);
            } else{
                world.Log("this move is impossiblu!!!!");
            }
        } else {
            verticalStr = vertical < 0 ? "up" :
                          vertical > 0 ? "down" :
                          "";
            horizontalStr = horizontal < 0 ? "left " :
                            horizontal > 0 ? "right " :
                            "";
            world.Log("Chosen move: [" + horizontalStr + verticalStr +
                      "] press Enter to Confirm", Color::WHITE);
        }
        world.Render();
    }

}

// TODO Collision!!

Organism *Human::Procreate() {
    world.Log("Human cannot procreate!");
    return nullptr;
}
