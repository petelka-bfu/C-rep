#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <stdexcept>
class Car
{
private:
    std::string brand;
    std::string model;      
    std::string VIN;        
    std::string state_number;
    int mileage;           
    std::vector<std::string> things;

public:
    Car();
    Car(const Car& other);
    Car(std::string br, std::string m, std::string V, std::string st_n, int mil, std::vector<std::string> th);
    ~Car();

    std::string getBrand() const;
    std::string getModel() const;
    std::string get_VIN() const;
    std::string getState_number() const;
    int getMileage() const;


    void SetThings(const std::vector<std::string>& thing);
    void setVIN(const std::string& newVIN);
    void setStateNumber(const std::string& newNumber);


    void displayInfo() const;
    void updateMileage(int prob);
    std::string RandomStateNumber() const;
    bool isValidVINChar(char c) const;
    bool isValidStateNumberChar(char c) const;
    bool isLetter(char c) const;

    Car operator+(const Car& other) const;
    Car& operator=(const Car& other);
    Car operator-(const Car& other) const;
    Car operator/(const Car& other) const;
    std::vector<std::string> getThings() const;
};


