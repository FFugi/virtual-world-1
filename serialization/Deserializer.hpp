//
// Created by ffugi on 21.04.18.
//

#ifndef VIRTUAL_WORLD_1_DESERIALIZER_HPP
#define VIRTUAL_WORLD_1_DESERIALIZER_HPP


#include <string>

class Deserializer {
    std::string toParse;
public:
    Deserializer(std::string toParse) : toParse(toParse) {}

    std::string GetPartOfString(std::size_t position);
};


#endif //VIRTUAL_WORLD_1_DESERIALIZER_HPP
