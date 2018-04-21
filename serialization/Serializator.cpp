//
// Created by ffugi on 07.04.18.
//
#include "Serializator.hpp"

void Serializator::WriteToFile(Serializable &item) {
    file << item.Serialize() << std::endl;
}

bool Serializator::OpenToSave(std::string fileName) {
    if(isOpen){
        Close();
    }
    file.open(fileName, std::fstream::out);
    isOpen = file.good();
    return file.good();
}

void Serializator::Close() {
    if(isOpen){
        file.close();
        isOpen = false;
    }
}

bool Serializator::IsOpenScuccesful() {
    return isOpen;
}
