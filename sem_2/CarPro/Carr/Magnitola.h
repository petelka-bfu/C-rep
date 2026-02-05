// Magnitola.h
#pragma once
#include <string>

struct Magnitola {

    std::string modelName;     
    std::string description;   
    double price;             

    Magnitola();
    Magnitola(const std::string& name, const std::string& desc, double price);

    void displayInfo() const;
};