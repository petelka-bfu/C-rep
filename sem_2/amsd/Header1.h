#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <stdexcept>

struct CarStereo;
class AutoWorkshop;

class Car {
private:
    std::string brand;
    std::string model;
    std::string VIN;
    std::string stateNumber;
    int mileage;
    std::vector<std::string> things;

    CarStereo* carStereo;
    std::string currentWorkshop;
    int fuel;
    int fuelConsumption;
    int fuelTankCapacity;

public:
    Car();
    Car(const Car& other);

    Car(const std::string& br, const std::string& mod,
        const std::string& vin, const std::string& stateNum,
        int mil, int fu, int fuelCap, int fuelCons,
        const std::vector<std::string>& th = {});

    ~Car();

    // Геттеры
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    std::string getVIN() const { return VIN; }
    std::string getStateNumber() const { return stateNumber; }
    int getMileage() const { return mileage; }
    int getFuel() const { return fuel; }
    int getFuelConsumption() const { return fuelConsumption; }
    int getFuelTankCapacity() const { return fuelTankCapacity; }
    std::vector<std::string> getThings() const { return things; }
    CarStereo* getCarStereo() const { return carStereo; }
    std::string getCurrentWorkshop() const { return currentWorkshop; }

    // Сеттеры
    void setBrand(const std::string& br) { brand = br; }
    void setModel(const std::string& mod) { model = mod; }
    void setVIN(const std::string& vin);
    void setStateNumber(const std::string& stateNum);
    void setMileage(int mil) {
        if (mil < 0) throw std::invalid_argument("Пробег не может быть отрицательным");
        mileage = mil;
    }
    void setFuel(int fu);
    void setFuelConsumption(int cons);
    void setFuelTankCapacity(int cap);
    void setThings(const std::vector<std::string>& th) { things = th; }
    void setCarStereo(CarStereo* stereo) { carStereo = stereo; }
    void setCurrentWorkshop(const std::string& workshop) { currentWorkshop = workshop; }



    void displayInfo() const;
    void updateMileage(int km);
    void addKilometers(int km); 
    void refuel(int liters);
    bool canTravel(int distance) const;

    // Операторы
    Car operator+(const Car& other) const;
    Car operator-(const Car& other) const;
    Car operator/(const Car& other) const;
    Car& operator=(const Car& other);


    std::string generateRandomStateNumber() const;
    bool isValidVIN(const std::string& vin) const;
    bool isValidStateNumber(const std::string& stateNum) const;

    // Дружественная функция
    friend void transferCarBetweenWorkshops(Car& car, AutoWorkshop& from,
        AutoWorkshop& to, int distance);
};