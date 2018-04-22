//
// Created by ffugi on 22.04.18.
//

#include "OrganismFactory.hpp"
#include "animals/Fox.hpp"
#include "animals/Wolf.hpp"
#include "animals/Sheep.hpp"
#include "animals/Antelope.hpp"
#include "animals/Tortoise.hpp"
#include "plants/Grass.hpp"
#include "plants/Sonchus.hpp"
#include "plants/WolfBerry.hpp"
#include "plants/Guarana.hpp"
#include "plants/Hogweed.hpp"
#include "animals/Human.hpp"

Organism *OrganismFactory::GetOrganism(std::string name, World &world) {
    if (name == "Fox") {
        return new Fox(world);
    } else if (name == "Wolf") {
        return new Wolf(world);
    } else if (name == "Sheep") {
        return new Sheep(world);
    } else if (name == "Antelope") {
        return new Antelope(world);
    } else if (name == "Tortoise") {
        return new Tortoise(world);
    } else if (name == "Grass") {
        return new Grass(world);
    } else if (name == "Sonchus") {
        return new Sonchus(world);
    } else if (name == "Wolf Berry") {
        return new WolfBerry(world);
    } else if (name == "Guarana") {
        return new Guarana(world);
    } else if (name == "Hogweed") {
        return new Hogweed(world);
    } else if (name == "Human") {
        return new Human(world);
    }
    return nullptr;
}

Organism *OrganismFactory::GetOrganism(std::string name, Position position,
                                       World &world) {
    if (name == "Fox") {
        return new Fox(position, world);
    } else if (name == "Wolf") {
        return new Wolf(position, world);
    } else if (name == "Sheep") {
        return new Sheep(position, world);
    } else if (name == "Antelope") {
        return new Antelope(position, world);
    } else if (name == "Tortoise") {
        return new Tortoise(position, world);
    } else if (name == "Grass") {
        return new Grass(position, world);
    } else if (name == "Sonchus") {
        return new Sonchus(position, world);
    } else if (name == "Wolf Berry") {
        return new WolfBerry(position, world);
    } else if (name == "Guarana") {
        return new Guarana(position, world);
    } else if (name == "Hogweed") {
        return new Hogweed(position, world);
    } else if (name == "Human") {
        return new Human(position, world);
    }
    return nullptr;
}
