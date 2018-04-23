//
// Created by ffugi on 01.04.18.
//

#ifndef VIRTUAL_WORLD_1_STRUCTURES_HPP
#define VIRTUAL_WORLD_1_STRUCTURES_HPP

struct Position {
    int x;
    int y;

    bool operator==(Position &other) {
        return x == other.x && y == other.y;
    }

    bool operator<(const Position &other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }
};

#endif //VIRTUAL_WORLD_1_STRUCTURES_HPP
