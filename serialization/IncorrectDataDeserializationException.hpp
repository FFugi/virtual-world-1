//
// Created by ffugi on 23.04.18.
//

#ifndef VIRTUAL_WORLD_1_INCORRECTDESERIALIZATIONEXCEPTION_HPP
#define VIRTUAL_WORLD_1_INCORRECTDESERIALIZATIONEXCEPTION_HPP


#include <exception>

class IncorrectDataDeserializationException : public std::exception {
public:
    char const *what() const throw() {
        return "Found incorrect data during deserialization";
    }

    ~IncorrectDataDeserializationException() throw() {}
};

#endif //VIRTUAL_WORLD_1_INCORRECTDESERIALIZATIONEXCEPTION_HPP
