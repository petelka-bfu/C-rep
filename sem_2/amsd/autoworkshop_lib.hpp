#pragma once
#ifndef AUTOWORKSHOP_LIB_HPP
#define AUTOWORKSHOP_LIB_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Предварительное объявление класса Car (чтобы избежать включения его заголовка)
class Car;

// ========== Структура Магнитола ==========
struct CarStereo {
    std::string modelName;
    std::string description;
    double price;

    // Конструкторы
    CarStereo();
    CarStereo(const std::string& name, const std::string& desc, double pr);

    // Методы
    void displayInfo() const;
};

// ========== Класс Автомастерская ==========
class AutoWorkshop {
private:
    std::string address;
    std::vector<CarStereo> availableStereos;
    std::vector<Car*> attachedCars; // Только указатели!

public:
    // Конструкторы
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

    // Работа с машинами (только через указатели)
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

#endif // AUTOWORKSHOP_LIB_HPP