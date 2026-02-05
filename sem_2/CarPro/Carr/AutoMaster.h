// AutoMaster.h
#pragma once
#include <string>
#include <vector>
#include "Magnitola.h"

class Car; 

class AutoMaster {
private:
    std::string address;                         
    std::vector<Magnitola> availableMagnitols;   
    std::vector<Car*> attachedCars;              

public:
    AutoMaster();                                  
    AutoMaster(const std::string& addr);          
    AutoMaster(const std::string& addr,            
        const std::vector<Magnitola>& magnitols);
    std::string getAddress() const { return address; }
    bool installMagnitola(const std::string& carNumber, int magnitolaIndex);

    void attachCar(Car* car);


}; 
