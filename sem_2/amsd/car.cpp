#include "Header1.h"
#include "autoworkshop_lib.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

//КОНСТРУКТОРЫ
Car::Car() :
    brand("Unknown"),
    model("Unknown"),
    VIN("00000000000000000"),
    stateNumber("A000AA000"),
    mileage(0),
    carStereo(nullptr),
    currentWorkshop("None"),
    fuel(0),
    fuelConsumption(10),
    fuelTankCapacity(60)
{
    cout << "Car: конструктор по умолчанию" << endl;
}

Car::Car(const Car& other) :
    brand(other.brand),
    model(other.model),
    VIN(other.VIN),
    stateNumber(other.stateNumber),
    mileage(other.mileage),
    things(other.things),
    carStereo(other.carStereo),
    currentWorkshop(other.currentWorkshop),
    fuel(other.fuel),
    fuelConsumption(other.fuelConsumption),
    fuelTankCapacity(other.fuelTankCapacity)
{
    cout << "Car: конструктор копирования" << endl;
}

Car::Car(const string& br, const string& mod,
    const string& vin, const string& stateNum,
    int mil, int fu, int fuelCap, int fuelCons,
    const vector<string>& th) :
    brand(br),
    model(mod),
    mileage(mil),
    things(th),
    carStereo(nullptr),
    currentWorkshop("None"),
    fuel(fu),
    fuelConsumption(fuelCons),
    fuelTankCapacity(fuelCap)
{
    if (vin.length() != 17) {
        VIN = "00000000000000000";
        cerr << "Предупреждение: неверный VIN, установлен по умолчанию" << endl;
    }
    else {
        VIN = vin;
    }

    if (stateNum.empty()) {
        stateNumber = "A000AA000";
        cerr << "Предупреждение: пустой госномер, установлен по умолчанию" << endl;
    }
    else {
        stateNumber = stateNum;
    }

    if (mil < 0) mileage = 0;
    if (fu < 0) fuel = 0;
    if (fuelCap <= 0) fuelTankCapacity = 60;
    if (fuelCons <= 0) fuelConsumption = 10;

    cout << "Car: создан автомобиль " << brand << " " << model << endl;
}

Car::~Car() {
    cout << "Car: уничтожен автомобиль " << brand << " " << model << endl;
}

//СЕТТЕРЫ
void Car::setVIN(const string& vin) {
    if (vin.length() != 17) {
        throw invalid_argument("VIN должен содержать ровно 17 символов");
    }

    for (char c : vin) {
        if (!(isdigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            throw invalid_argument("VIN содержит недопустимые символы");
        }
    }

    VIN = vin;
}

void Car::setStateNumber(const string& stateNum) {
    if (stateNum.empty()) {
        throw invalid_argument("Госномер не может быть пустым");
    }

    if (stateNum.length() < 6 || stateNum.length() > 9) {
        throw invalid_argument("Госномер должен быть от 6 до 9 символов");
    }

    bool hasDigit = false;
    bool hasLetter = false;

    for (char c : stateNum) {
        if (isdigit(c)) hasDigit = true;
        if (isalpha(c)) hasLetter = true;
        if (hasDigit && hasLetter) break;
    }

    if (!hasDigit || !hasLetter) {
        throw invalid_argument("Госномер должен содержать и буквы, и цифры");
    }

    stateNumber = stateNum;
}

void Car::setFuel(int fu) {
    if (fu < 0) {
        throw invalid_argument("Количество топлива не может быть отрицательным");
    }
    if (fu > fuelTankCapacity) {
        throw out_of_range("Количество топлива превышает объем бака");
    }
    fuel = fu;
}

void Car::setFuelConsumption(int cons) {
    if (cons <= 0) {
        throw invalid_argument("Расход топлива должен быть положительным");
    }
    fuelConsumption = cons;
}

void Car::setFuelTankCapacity(int cap) {
    if (cap <= 0) {
        throw invalid_argument("Объем бака должен быть положительным");
    }
    fuelTankCapacity = cap;
    // Если текущее топливо больше нового объема бака
    if (fuel > cap) {
        fuel = cap;
    }
}

//ОТОБРАЖЕНИЕ
void Car::displayInfo() const {
    cout << "\n=== ИНФОРМАЦИЯ ОБ АВТОМОБИЛЕ ===" << endl;
    cout << "Марка: " << brand << endl;
    cout << "Модель: " << model << endl;
    cout << "VIN: " << VIN << endl;
    cout << "Госномер: " << stateNumber << endl;
    cout << "Пробег: " << mileage << " км" << endl;
    cout << "Топливо: " << fuel << "/" << fuelTankCapacity << " л" << endl;
    cout << "Расход: " << fuelConsumption << " л/100км" << endl;
    cout << "Мастерская: " << currentWorkshop << endl;

    if (carStereo) {
        cout << "Магнитола: " << carStereo->modelName << endl;
    }
    else {
        cout << "Магнитола: не установлена" << endl;
    }

    cout << "Вещей в багажнике: " << things.size() << endl;
    for (size_t i = 0; i < things.size() && i < 5; ++i) {
        cout << "  " << i + 1 << ". " << things[i] << endl;
    }
    if (things.size() > 5) {
        cout << "  ... и еще " << (things.size() - 5) << " вещей" << endl;
    }
    cout << "=================================" << endl;
}
//ПРОБЕГ
void Car::updateMileage(int km) {
    if (km < 0) {
        throw invalid_argument("Пробег для скрутки должен быть положительным");
    }
    if (mileage - km < 0) {
        throw invalid_argument("Нельзя скрутить больше текущего пробега");
    }
    mileage -= km;
    cout << "Пробег скручен на " << km << " км. Новый пробег: " << mileage << " км" << endl;
}
//КИЛОМЕТРИКИ
void Car::addKilometers(int km) {
    if (km <= 0) {
        throw invalid_argument("Пробег должен быть положительным");
    }

    double fuelNeeded = (km * fuelConsumption) / 100.0;

    if (fuel < fuelNeeded) {
        throw out_of_range("Недостаточно топлива. Нужно " + to_string(fuelNeeded) +
            " л, а есть " + to_string(fuel) + " л");
    }

    mileage += km;
    fuel -= static_cast<int>(fuelNeeded);
    cout << "Проехали " << km << " км. Израсходовано " << fuelNeeded << " л топлива." << endl;
}
//ЗАПРАВОЧКА
void Car::refuel(int liters) {
    if (liters <= 0) {
        throw invalid_argument("Количество топлива должно быть положительным");
    }

    if (fuel + liters > fuelTankCapacity) {
        int actualLiters = fuelTankCapacity - fuel;
        fuel = fuelTankCapacity;
        cout << "Заправлено " << actualLiters << " л (бак полный)" << endl;
    }
    else {
        fuel += liters;
        cout << "Заправлено " << liters << " л" << endl;
    }
}
//ПРОВЕРКА
bool Car::canTravel(int distance) const {
    if (distance <= 0) return false;
    double fuelNeeded = (distance * fuelConsumption) / 100.0;
    return fuel >= fuelNeeded;
}

//ОПЕРАТОРЫ
Car Car::operator+(const Car& other) const {
    Car result;
    result.brand = this->brand;
    result.model = this->model;
    result.mileage = (this->mileage + other.mileage) / 2;
    result.fuel = min(this->fuel, other.fuel);
    result.fuelConsumption = (this->fuelConsumption + other.fuelConsumption) / 2;
    result.fuelTankCapacity = max(this->fuelTankCapacity, other.fuelTankCapacity);

    // Генерируем уникальный госномер
    result.stateNumber = generateRandomStateNumber();

    // Объединяем вещи
    result.things = this->things;
    result.things.insert(result.things.end(),
        other.things.begin(), other.things.end());

    cout << "Создан новый автомобиль (оператор +)" << endl;
    return result;
}

Car Car::operator-(const Car& other) const {
    Car result = *this + other; // Используем operator+

    // Уникальные вещи
    vector<string> uniqueThings;
    for (const auto& item : result.things) {
        if (find(uniqueThings.begin(), uniqueThings.end(), item) == uniqueThings.end()) {
            uniqueThings.push_back(item);
        }
    }
    result.things = uniqueThings;

    return result;
}

Car Car::operator/(const Car& other) const {
    Car result;
    result.brand = this->brand;

    // Общие вещи
    for (const auto& item1 : this->things) {
        for (const auto& item2 : other.things) {
            if (item1 == item2) {
                result.things.push_back(item1);
                break;
            }
        }
    }

    result.stateNumber = generateRandomStateNumber();
    result.fuel = 0; // При делении топливо не передается

    return result;
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        VIN = other.VIN;
        stateNumber = other.stateNumber;
        mileage = other.mileage;
        things = other.things;
        carStereo = other.carStereo;
        currentWorkshop = other.currentWorkshop;
        fuel = other.fuel;
        fuelConsumption = other.fuelConsumption;
        fuelTankCapacity = other.fuelTankCapacity;
    }
    return *this;
}
//ВЕЛИКИЙ РАНДОМММ
string Car::generateRandomStateNumber() const {
    static const string letters = "ABCEHKMOPTXY";
    static random_device rd;
    static mt19937 gen(rd());

    string result;
    uniform_int_distribution<int> letterDist(0, letters.size() - 1);
    uniform_int_distribution<int> numDist(100, 999);
    uniform_int_distribution<int> regionDist(1, 99);

    result += letters[letterDist(gen)];
    result += to_string(numDist(gen));
    result += letters[letterDist(gen)];
    result += letters[letterDist(gen)];

    int region = regionDist(gen);
    if (region < 10) {
        result += "0" + to_string(region);
    }
    else {
        result += to_string(region);
    }

    return result;
}

bool Car::isValidVIN(const string& vin) const {
    if (vin.length() != 17) return false;
    for (char c : vin) {
        if (!(isdigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool Car::isValidStateNumber(const string& stateNum) const {
    if (stateNum.length() < 6 || stateNum.length() > 9) return false;

    bool hasDigit = false;
    bool hasLetter = false;

    for (char c : stateNum) {
        if (isdigit(c)) hasDigit = true;
        if (isalpha(c)) hasLetter = true;
    }

    return hasDigit && hasLetter;
}

//ДРУЖЕСТВЕННАЯ ФУНКЦИЯ
void transferCarBetweenWorkshops(Car& car, AutoWorkshop& from,
    AutoWorkshop& to, int distance) {
    try {
        cout << "\n>>> Начинаем перегон автомобиля" << endl;

        // Проверяем прикрепленность
        if (!from.isCarAttached(&car)) {
            throw runtime_error("Автомобиль не прикреплен к мастерской отправления");
        }

        // Проверяем возможность поездки
        if (!car.canTravel(distance)) {
            throw runtime_error("Недостаточно топлива для перегона");
        }

        // Поездка
        car.addKilometers(distance);

        // Переприкрепление
        from.detachCar(&car);
        to.attachCar(&car);
        car.setCurrentWorkshop(to.getAddress());

        cout << ">>> Перегон успешно завершен!" << endl;

    }
    catch (const exception& e) {
        cerr << "Ошибка при перегоне: " << e.what() << endl;
        throw; // Перебрасываем исключение дальше
    }
}