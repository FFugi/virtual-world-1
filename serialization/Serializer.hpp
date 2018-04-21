//
// Created by ffugi on 07.04.18.
//

#ifndef VIRTUAL_WORLD_1_SERIALIZATOR_HPP
#define VIRTUAL_WORLD_1_SERIALIZATOR_HPP


#include <vector>
#include <fstream>
#include "Serializable.hpp"

class Serializer {
private:
    std::fstream file;
    bool isOpen;
public:
    Serializer() :isOpen(false){}
    ~Serializer(){
        file.close();
    }
    void WriteToFile(Serializable &item);
    bool IsOpenSuccessful();
    bool OpenToSave(std::string fileName);
    void Close();
};


#endif //VIRTUAL_WORLD_1_SERIALIZATOR_HPP
