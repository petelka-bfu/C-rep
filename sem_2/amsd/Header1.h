#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <stdexcept>

// Предварительное объявление
struct CarStereo;
class AutoWorkshop;

class Car
{
private:
    std::string brand;
    std::string model;
    std::string VIN;
    std::string stateNumber;
    int mileage;
    std::vector<std::string> things;

    // Новые поля для интеграции с библиотекой
    CarStereo* installedStereo;
    std::string currentWorkshop;
    int fuel;
    int fuelTankCapacity;
    int fuelConsumption;

public:
    Car();
    Car(const Car& other);
    Car(std::string br, std::string m, std::string V, std::string st_n,
        std::string workshop, CarStereo* stereo, int mil, int fu,
        int fu_cap, int fu_cons, std::vector<std::string> th);
    ~Car();

    // Геттеры
    std::string getBrand() const;
    std::string getModel() const;
    std::string getVIN() const;
    std::string getStateNumber() const;
    int getMileage() const;
    int getFuel() const;
    int getFuelTankCapacity() const;
    int getFuelConsumption() const;
    std::vector<std::string> getThings() const;
    CarStereo* getInstalledStereo() const;
    std::string getCurrentWorkshop() const;

    // Сеттеры
    void SetThings(const std::vector<std::string>& thing);
    void setVIN(const std::string& newVIN);
    void setStateNumber(const std::string& newNumber);
    void setInstalledStereo(CarStereo* stereo);
    void setCurrentWorkshop(const std::string& workshop);
    void setFuel(int f);
    void setFuelTankCapacity(int cap);
    void setFuelConsumption(int cons);

    // Новые методы
    void refuel(int liters);
    bool canTravel(int distance) const;
    void travel(int distance);
    void changeStereo(CarStereo* newStereo);

    // Существующие методы
    void displayInfo() const;
    void updateMileage(int prob);
    std::string randomStateNumber() const;
    bool isValidVINChar(char c) const;
    bool isValidStateNumberChar(char c) const;
    bool isLetter(char c) const;

    // Операторы
    Car operator+(const Car& other) const;
    Car& operator=(const Car& other);
    Car operator-(const Car& other) const;
    Car operator/(const Car& other) const;

    // Дружественная функция
    friend void transferCarBetweenWorkshops(Car& car, AutoWorkshop& from, AutoWorkshop& to, int distance);
};