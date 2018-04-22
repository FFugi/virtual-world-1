//
// Created by ffugi on 21.04.18.
//

#include "Parser.hpp"

std::string Parser::GetPartOfString(std::size_t position) {
    // TODO what if null
    if (position == 0) {
        auto end = toParse.find(',');
        return toParse.substr(0, end);
    }
    std::size_t startPosition = 0;
    for (std::size_t i = 0; i < position; i++) {
        startPosition = toParse.find(',', startPosition + 1);
        if(startPosition == std::string::npos){
            return "";
        }
    }
    auto end = toParse.find(',', startPosition + 1);
    return toParse.substr(startPosition + 1, end - startPosition - 1);
}
