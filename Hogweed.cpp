//
// Created by ffugi on 06.04.18.
//

#include "Hogweed.hpp"

void Hogweed::Action() {
    std::vector<Position> positions = world.GetNeighbourFields(position);
    std::vector<Organism*> neighbours;
    for(auto pos : positions){
        Organism * neighbour = world.GetAtField(pos);
        if(neighbour != nullptr){
            neighbour->Kill();
        }
    }
}
