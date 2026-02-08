#pragma once
#ifndef AUTOWORKSHOP_LIB_HPP
#define AUTOWORKSHOP_LIB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>


class Car;

struct CarStereo {
    std::string modelName;
    std::string description;
    double price;

    CarStereo();
    CarStereo(const std::string& name, const std::string& desc, double pr);

    void displayInfo() const;
};

class AutoWorkshop {
private:
    std::string address;
    std::vector<CarStereo> availableStereos;
    std::vector<Car*> attachedCars;

public:

    AutoWorkshop();
    AutoWorkshop(const std::string& addr);
    AutoWorkshop(const AutoWorkshop& other);
    ~AutoWorkshop();

    // Геттеры
    std::string getAddress() const;
    std::vector<CarStereo> getAvailableStereos() const;
    std::vector<Car*> getAttachedCars() const;

    // Сеттеры
    void setAddress(const std::string& addr);

    // Основные методы
    void addStereo(const CarStereo& stereo);
    void addStereos(const std::vector<CarStereo>& stereos);

    // Работа с машинами
    void attachCar(Car* car);
    void detachCar(Car* car);
    bool isCarAttached(const Car* car) const;

    // Установка магнитолы на машину
    bool installStereoToCar(Car* car, const std::string& stereoModel);

    // Отображение информации
    void displayInfo() const;

    // Поиск магнитолы по модели
    CarStereo* findStereo(const std::string& modelName);
};

#endif 