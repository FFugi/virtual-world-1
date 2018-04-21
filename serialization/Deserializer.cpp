//
// Created by ffugi on 21.04.18.
//

#include "Deserializer.hpp"

std::string Deserializer::GetPartOfString(std::size_t position) {
    if (position == 0) {
        auto end = toParse.find(',');
        return toParse.substr(0, end);
    }
    std::size_t startPosition = 0;
    for (std::size_t i = 0; i < position; i++) {
        startPosition = toParse.find(',', startPosition + 1);
    }
    auto end = toParse.find(',', startPosition + 1);
    return toParse.substr(startPosition + 1, end - startPosition - 1);
}
