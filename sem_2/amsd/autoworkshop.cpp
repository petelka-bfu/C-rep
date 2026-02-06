#include "autoworkshop_lib.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

// ========== Реализация CarStereo ==========

CarStereo::CarStereo()
    : modelName("Unknown"), description("No description"), price(0.0) {
}

CarStereo::CarStereo(const string& name, const string& desc, double pr)
    : modelName(name), description(desc), price(pr) {
}

void CarStereo::displayInfo() const {
    cout << "  Модель: " << modelName << endl;
    cout << "  Описание: " << description << endl;
    cout << "  Цена: " << price << " руб." << endl;
}

// ========== Реализация AutoWorkshop ==========

AutoWorkshop::AutoWorkshop() : address("Не указан") {
    cout << "Создана автомастерская по адресу: " << address << endl;
}

AutoWorkshop::AutoWorkshop(const string& addr) : address(addr) {
    cout << "Создана автомастерская по адресу: " << address << endl;
}

AutoWorkshop::AutoWorkshop(const AutoWorkshop& other)
    : address(other.address),
    availableStereos(other.availableStereos),
    attachedCars(other.attachedCars) {
    cout << "Скопирована автомастерская с адресом: " << address << endl;
}

AutoWorkshop::~AutoWorkshop() {
    cout << "Автомастерская по адресу " << address << " закрыта" << endl;
}

// Геттеры
string AutoWorkshop::getAddress() const {
    return address;
}

vector<CarStereo> AutoWorkshop::getAvailableStereos() const {
    return availableStereos;
}

vector<Car*> AutoWorkshop::getAttachedCars() const {
    return attachedCars;
}

// Сеттеры
void AutoWorkshop::setAddress(const string& addr) {
    address = addr;
}

// Методы для работы с магнитолами
void AutoWorkshop::addStereo(const CarStereo& stereo) {
    availableStereos.push_back(stereo);
    cout << "Добавлена магнитола: " << stereo.modelName << endl;
}

void AutoWorkshop::addStereos(const vector<CarStereo>& stereos) {
    availableStereos.insert(availableStereos.end(), stereos.begin(), stereos.end());
    cout << "Добавлено " << stereos.size() << " магнитол(ы)" << endl;
}

// Методы для работы с машинами
void AutoWorkshop::attachCar(Car* car) {
    if (car == nullptr) {
        throw invalid_argument("Нельзя прикрепить нулевой указатель на машину");
    }

    // Проверяем, не прикреплена ли уже эта машина
    auto it = find(attachedCars.begin(), attachedCars.end(), car);
    if (it == attachedCars.end()) {
        attachedCars.push_back(car);
        cout << "Машина прикреплена к автомастерской " << address << endl;
    }
    else {
        cout << "Машина уже прикреплена к этой автомастерской" << endl;
    }
}

void AutoWorkshop::detachCar(Car* car) {
    if (car == nullptr) return;

    auto it = find(attachedCars.begin(), attachedCars.end(), car);
    if (it != attachedCars.end()) {
        attachedCars.erase(it);
        cout << "Машина откреплена от автомастерской " << address << endl;
    }
}

bool AutoWorkshop::isCarAttached(const Car* car) const {
    if (car == nullptr) return false;

    return find(attachedCars.begin(), attachedCars.end(), car) != attachedCars.end();
}

// Установка магнитолы на машину
bool AutoWorkshop::installStereoToCar(Car* car, const string& stereoModel) {
    if (car == nullptr) {
        cout << "Ошибка: передан нулевой указатель на машину" << endl;
        return false;
    }

    // Проверяем, прикреплена ли машина к этой мастерской
    if (!isCarAttached(car)) {
        cout << "Машина не прикреплена к этой автомастерской" << endl;
        return false;
    }

    // Ищем магнитолу
    CarStereo* foundStereo = nullptr;
    for (auto& stereo : availableStereos) {
        if (stereo.modelName == stereoModel) {
            foundStereo = &stereo;
            break;
        }
    }

    if (foundStereo == nullptr) {
        cout << "Магнитола '" << stereoModel << "' не найдена в мастерской" << endl;
        return false;
    }

    // Устанавливаем магнитолу (нужен метод в классе Car)
    // car->installStereo(foundStereo); // Этот метод нужно добавить в класс Car

    cout << "Магнитола '" << stereoModel << "' установлена на машину" << endl;
    return true;
}

// Поиск магнитолы
CarStereo* AutoWorkshop::findStereo(const string& modelName) {
    for (auto& stereo : availableStereos) {
        if (stereo.modelName == modelName) {
            return &stereo;
        }
    }
    return nullptr;
}

// Отображение информации
void AutoWorkshop::displayInfo() const {
    cout << "\n=== Информация об автомастерской ===" << endl;
    cout << "Адрес: " << address << endl;

    cout << "\nДоступные магнитолы (" << availableStereos.size() << " шт.):" << endl;
    if (availableStereos.empty()) {
        cout << "  Нет доступных магнитол" << endl;
    }
    else {
        for (size_t i = 0; i < availableStereos.size(); ++i) {
            cout << i + 1 << ". ";
            availableStereos[i].displayInfo();
        }
    }

    cout << "\nПрикрепленные машины (" << attachedCars.size() << " шт.):" << endl;
    if (attachedCars.empty()) {
        cout << "  Нет прикрепленных машин" << endl;
    }
    else {
        for (size_t i = 0; i < attachedCars.size(); ++i) {
            if (attachedCars[i] != nullptr) {
                // Для вывода информации о машине нужен доступ к её методам
                // Можно добавить метод в Car для получения базовой информации
                cout << "  " << i + 1 << ". [Указатель на машину]" << endl;
            }
        }
    }
    cout << "====================================\n" << endl;
}