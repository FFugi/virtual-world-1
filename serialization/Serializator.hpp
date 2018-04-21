//
// Created by ffugi on 07.04.18.
//

#ifndef VIRTUAL_WORLD_1_SERIALIZATOR_HPP
#define VIRTUAL_WORLD_1_SERIALIZATOR_HPP


#include <vector>
#include <fstream>
#include "Serializable.hpp"

class Serializator {
private:
    std::fstream file;
    bool isOpen;
public:
    Serializator() :isOpen(false){}
    ~Serializator(){
        file.close();
    }
    void WriteToFile(Serializable &item);
    bool IsOpenScuccesful();
    bool OpenToSave(std::string fileName);
    void Close();
};


#endif //VIRTUAL_WORLD_1_SERIALIZATOR_HPP
