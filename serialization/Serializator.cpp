//
// Created by ffugi on 07.04.18.
//
#include "Serializator.hpp"

void Serializator::WriteToFile(Serializable &item) {
    file << item.Serialize() << std::endl;
}

void Serializator::OpenToSave(std::string fileName) {
    if(isOpen){
        Close();
    }
    file.open(fileName, std::fstream::out);
}

void Serializator::Close() {
    if(isOpen){
        file.close();
        isOpen = false;
    }
}
