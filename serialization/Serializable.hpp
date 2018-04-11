//
// Created by ffugi on 07.04.18.
//

#ifndef VIRTUAL_WORLD_1_SERIALIZABLE_HPP
#define VIRTUAL_WORLD_1_SERIALIZABLE_HPP


#include <string>

class Serializable {
public:
    virtual std::string Serialize() = 0;
    virtual void Deserialize(std::string data) = 0;
};


#endif //VIRTUAL_WORLD_1_SERIALIZABLE_HPP
