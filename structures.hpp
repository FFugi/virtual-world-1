//
// Created by ffugi on 01.04.18.
//

#ifndef VIRTUAL_WORLD_1_STRUCTURES_HPP
#define VIRTUAL_WORLD_1_STRUCTURES_HPP
struct Position{
    int x;
    int y;
    inline bool operator == (Position other){
        return x == other.x && y == other.y;
    }
};

#endif //VIRTUAL_WORLD_1_STRUCTURES_HPP
