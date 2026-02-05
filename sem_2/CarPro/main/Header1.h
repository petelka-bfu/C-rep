#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <stdexcept>
using namespace std;
class Car
{
private:
    std::string brand;
    std::string model;      
    std::string VIN;        
    std::string state_number;
    std::string car_stereo;//
    std::string servis;//
    int fuel_tank_cap;//
    int fuel_cons;//
    int fuel;//
    int mileage;     
    std::vector<std::string> things;

public:
    Car();
    Car(const Car& other);
    Car(string br, string m, string V, string st_n,
        string serv, string ster, int mil, int fu,
        int fu_cap, int fu_tan, vector<string> th);
    ~Car();

    std::string getBrand() const;
    std::string getModel() const;
    std::string get_VIN() const;
    std::string getState_number() const;
    std::string getServis() const;
    std::string getCar_stereo() const;
    int getMileage() const;
    int getFuel_cons() const;
    int getFuel() const;


    void SetThings(const std::vector<std::string>& thing);
    void setVIN(const std::string& newVIN);
    void setStateNumber(const std::string& newNumber);
    void setCarStereo(const std::string& stereo);


    void refueling();
    void Stereo_change();
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

    friend void distillation(Car& car);
};


