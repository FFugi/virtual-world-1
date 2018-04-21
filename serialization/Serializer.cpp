//
// Created by ffugi on 07.04.18.
//
#include "Serializer.hpp"

void Serializer::WriteToFile(Serializable &item) {
    file << item.Serialize() << std::endl;
}

bool Serializer::OpenToSave(std::string fileName) {
    if(isOpen){
        Close();
    }
    file.open(fileName, std::fstream::out);
    isOpen = file.good();
    return file.good();
}

void Serializer::Close() {
    if(isOpen){
        file.close();
        isOpen = false;
    }
}

bool Serializer::IsOpenSuccessful() {
    return isOpen;
}
