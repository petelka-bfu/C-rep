#include "Header1.h"
#include "autoworkshop_lib.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ========== КОНСТРУКТОРЫ И ДЕСТРУКТОР ==========
Car::Car() :
    brand("Неизвестно"),
    model("Неизвестно"),
    VIN("00000000000000000"),
    stateNumber("A777AA777"),
    mileage(0),
    things({}),
    installedStereo(nullptr),
    currentWorkshop("Не прикреплена"),
    fuel(0),
    fuelTankCapacity(60),
    fuelConsumption(10)
{
    cout << "Конструктор Car по умолчанию" << endl;
}

Car::Car(const Car& other) :
    brand(other.brand),
    model(other.model),
    VIN(other.VIN),
    stateNumber(other.stateNumber),
    mileage(other.mileage),
    things(other.things),
    installedStereo(other.installedStereo),
    currentWorkshop(other.currentWorkshop),
    fuel(other.fuel),
    fuelTankCapacity(other.fuelTankCapacity),
    fuelConsumption(other.fuelConsumption)
{
    cout << "Конструктор копирования Car" << endl;
}

Car::Car(string br, string m, string V, string st_n,
    string workshop, CarStereo* stereo, int mil, int fu,
    int fu_cap, int fu_cons, vector<string> th)
{
    brand = br;
    model = m;
    currentWorkshop = workshop;
    installedStereo = stereo;
    mileage = mil;
    fuel = fu;
    fuelTankCapacity = fu_cap;
    fuelConsumption = fu_cons;

    setVIN(V);
    setStateNumber(st_n);
    SetThings(th);

    cout << "Параметризированный конструктор Car" << endl;
}

Car::~Car() {
    cout << "Деструктор Car для " << brand << " " << model << endl;
    // Не удаляем installedStereo, т.к. он принадлежит AutoWorkshop
}

// ========== ГЕТТЕРЫ ==========
string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
string Car::getVIN() const { return VIN; }
string Car::getStateNumber() const { return stateNumber; }
int Car::getMileage() const { return mileage; }
int Car::getFuel() const { return fuel; }
int Car::getFuelTankCapacity() const { return fuelTankCapacity; }
int Car::getFuelConsumption() const { return fuelConsumption; }
vector<string> Car::getThings() const { return things; }
CarStereo* Car::getInstalledStereo() const { return installedStereo; }
string Car::getCurrentWorkshop() const { return currentWorkshop; }

// ========== СЕТТЕРЫ ==========
void Car::SetThings(const vector<string>& thing) {
    things = thing;
}

void Car::setVIN(const string& newVIN) {
    if (newVIN.length() != 17) {
        throw length_error("Длина VIN должна быть ровно 17 символов");
    }

    for (char c : newVIN) {
        if (!isValidVINChar(c)) {
            throw invalid_argument("Найден недопустимый символ в VIN");
        }
    }

    VIN = newVIN;
}

void Car::setStateNumber(const string& newNumber) {
    if (newNumber.empty()) {
        throw invalid_argument("Государственный номер не может быть пустым");
    }

    if (newNumber.length() < 6 || newNumber.length() > 9) {
        throw length_error("Государственный номер должен содержать от 6 до 9 символов");
    }

    bool hasLetter = false;
    bool hasDigit = false;

    for (char c : newNumber) {
        if (isdigit(c)) {
            hasDigit = true;
        }
        else if (isLetter(c)) {
            hasLetter = true;
        }
    }

    if (!hasLetter || !hasDigit) {
        throw invalid_argument("Государственный номер должен содержать хотя бы одну букву и одну цифру");
    }

    stateNumber = newNumber;
}

void Car::setInstalledStereo(CarStereo* stereo) {
    installedStereo = stereo;
    cout << "Установлена магнитола на автомобиль " << brand << " " << model << endl;
    if (stereo) {
        cout << "  Модель магнитолы: " << stereo->modelName << endl;
    }
}

void Car::setCurrentWorkshop(const string& workshop) {
    currentWorkshop = workshop;
    cout << "Автомобиль " << brand << " " << model
        << " прикреплен к мастерской: " << workshop << endl;
}

void Car::setFuel(int f) {
    if (f < 0) {
        throw invalid_argument("Количество топлива не может быть отрицательным");
    }
    if (f > fuelTankCapacity) {
        throw out_of_range("Количество топлива превышает объем бака");
    }
    fuel = f;
    cout << "Установлено топливо: " << fuel << " л" << endl;
}

void Car::setFuelTankCapacity(int cap) {
    if (cap <= 0) {
        throw invalid_argument("Объем бака должен быть положительным");
    }
    fuelTankCapacity = cap;
    cout << "Установлен объем бака: " << fuelTankCapacity << " л" << endl;
}

void Car::setFuelConsumption(int cons) {
    if (cons <= 0) {
        throw invalid_argument("Расход топлива должен быть положительным");
    }
    fuelConsumption = cons;
    cout << "Установлен расход топлива: " << fuelConsumption << " л/100км" << endl;
}

// ========== НОВЫЕ МЕТОДЫ ДЛЯ РАБОТЫ С ТОПЛИВОМ И МАГНИТОЛАМИ ==========

// Заправка автомобиля
void Car::refuel(int liters) {
    if (liters <= 0) {
        throw invalid_argument("Количество топлива должно быть положительным");
    }

    if (fuel + liters > fuelTankCapacity) {
        int maxRefuel = fuelTankCapacity - fuel;
        fuel = fuelTankCapacity;
        cout << "Заправлено " << maxRefuel << " л (бак полный). Перелив "
            << (liters - maxRefuel) << " л." << endl;
    }
    else {
        fuel += liters;
        cout << "Заправлено " << liters << " л. Теперь в баке " << fuel << " л." << endl;
    }
}

// Проверка возможности поездки
bool Car::canTravel(int distance) const {
    if (distance <= 0) {
        return false;
    }

    double fuelNeeded = (distance * fuelConsumption) / 100.0;
    return fuel >= fuelNeeded;
}

// Поездка с учетом расхода топлива
void Car::travel(int distance) {
    if (distance <= 0) {
        throw invalid_argument("Расстояние должно быть положительным");
    }

    double fuelNeeded = (distance * fuelConsumption) / 100.0;

    if (fuelNeeded > fuel) {
        throw out_of_range("Недостаточно топлива для поездки. Нужно заправиться!");
    }

    mileage += distance;
    fuel -= static_cast<int>(fuelNeeded);

    cout << "Проехали " << distance << " км. Израсходовано " << fuelNeeded
        << " л топлива. Осталось " << fuel << " л." << endl;
}

// Замена магнитолы
void Car::changeStereo(CarStereo* newStereo) {
    cout << "Замена магнитолы на автомобиле " << brand << " " << model << endl;

    if (installedStereo) {
        cout << "  Старая магнитола: " << installedStereo->modelName << endl;
    }
    else {
        cout << "  Старая магнитола: не установлена" << endl;
    }

    installedStereo = newStereo;

    if (newStereo) {
        cout << "  Новая магнитола: " << newStereo->modelName << endl;
        cout << "  Цена: " << newStereo->price << " руб." << endl;
    }
    else {
        cout << "  Новая магнитола: удалена" << endl;
    }
}

// ========== БУЛЕВЫЕ ФУНКЦИИ ВАЛИДАЦИИ ==========
bool Car::isValidVINChar(char c) const {
    return isdigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool Car::isValidStateNumberChar(char c) const {
    if (c >= '0' && c <= '9') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'А' && c <= 'Я') return true;
    if (c >= 'а' && c <= 'я') return true;
    return false;
}

bool Car::isLetter(char c) const {
    unsigned char uc = static_cast<unsigned char>(c);
    return (uc >= 'A' && uc <= 'Z') || (uc >= 'a' && uc <= 'z');
}

// ========== РАНДОМНЫЙ ГОСНОМЕР ==========
string Car::randomStateNumber() const {
    random_device rd;
    mt19937 gen(rd());

    string letters = "ABCEHKMOPTXY";
    if (letters.empty()) {
        throw runtime_error("Letters string is empty");
    }

    string result;
    uniform_int_distribution<int> letterDist(0, static_cast<int>(letters.size()) - 1);

    result += letters[letterDist(gen)];

    uniform_int_distribution<int> digitDist(1, 999);
    int num = digitDist(gen);
    if (num < 10) {
        result += "00" + to_string(num);
    }
    else if (num < 100) {
        result += "0" + to_string(num);
    }
    else {
        result += to_string(num);
    }

    result += letters[letterDist(gen)];
    result += letters[letterDist(gen)];

    uniform_int_distribution<int> regionDist(1, 99);
    int region = regionDist(gen);
    if (region < 10) {
        result += "0" + to_string(region);
    }
    else {
        result += to_string(region);
    }

    return result;
}

// ========== ОТОБРАЖЕНИЕ ИНФОРМАЦИИ ==========
void Car::displayInfo() const {
    cout << "\n=== ИНФОРМАЦИЯ ОБ АВТОМОБИЛЕ ===" << endl;
    cout << "Марка: " << brand << endl;
    cout << "Модель: " << model << endl;
    cout << "VIN: " << VIN << endl;
    cout << "Гос. номер: " << stateNumber << endl;
    cout << "Пробег: " << mileage << " км" << endl;

    cout << "Топливо: " << fuel << "/" << fuelTankCapacity << " л" << endl;
    cout << "Расход: " << fuelConsumption << " л/100км" << endl;
    cout << "Текущая мастерская: " << currentWorkshop << endl;

    if (installedStereo) {
        cout << "Установленная магнитола:" << endl;
        cout << "  Модель: " << installedStereo->modelName << endl;
        cout << "  Описание: " << installedStereo->description << endl;
        cout << "  Цена: " << installedStereo->price << " руб." << endl;
    }
    else {
        cout << "Магнитола: не установлена" << endl;
    }

    cout << "Вещи в багажнике (" << things.size() << " шт.):" << endl;
    if (things.empty()) {
        cout << "  Багажник пуст" << endl;
    }
    else {
        for (size_t i = 0; i < things.size(); ++i) {
            cout << "  " << i + 1 << ". " << things[i] << endl;
        }
    }
    cout << "================================\n" << endl;
}

// ========== ОПЕРАТОРЫ ==========
Car Car::operator+(const Car& other) const {
    Car newCar;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);

    if (dist(gen) == 0) {
        newCar.brand = this->brand;
        cout << "Выбрана марка первого автомобиля: " << this->brand << endl;
    }
    else {
        newCar.brand = other.brand;
        cout << "Выбрана марка второго автомобиля: " << other.brand << endl;
    }

    string newStateNumber;
    int attempts = 0;
    do {
        newStateNumber = newCar.randomStateNumber();
        cout << "Сгенерирован номер: " << newStateNumber << " (длина: " << newStateNumber.length() << ")" << endl;
        attempts++;
        if (attempts > 10) {
            newStateNumber = "A111AA77";
            break;
        }
    } while (newStateNumber == this->stateNumber || newStateNumber == other.stateNumber);

    newCar.setStateNumber(newStateNumber);

    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());
    newCar.SetThings(combinedThings);

    // Копируем другие параметры
    newCar.model = this->model;
    newCar.installedStereo = this->installedStereo;
    newCar.currentWorkshop = this->currentWorkshop;
    newCar.fuel = (this->fuel + other.fuel) / 2;
    newCar.fuelTankCapacity = max(this->fuelTankCapacity, other.fuelTankCapacity);
    newCar.fuelConsumption = (this->fuelConsumption + other.fuelConsumption) / 2;

    cout << "Создан новый автомобиль (оператор +)!" << endl;
    return newCar;
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        VIN = other.VIN;
        stateNumber = other.stateNumber;
        mileage = other.mileage;
        things = other.things;
        installedStereo = other.installedStereo;
        currentWorkshop = other.currentWorkshop;
        fuel = other.fuel;
        fuelTankCapacity = other.fuelTankCapacity;
        fuelConsumption = other.fuelConsumption;

        cout << "Выполнено присваивание для автомобиля " << brand << " " << model << endl;
    }
    return *this;
}

Car Car::operator-(const Car& other) const {
    Car newCar;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);

    if (dist(gen) == 0) {
        newCar.brand = this->brand;
        cout << "Выбрана марка первого автомобиля: " << this->brand << endl;
    }
    else {
        newCar.brand = other.brand;
        cout << "Выбрана марка второго автомобиля: " << other.brand << endl;
    }

    string newStateNumber;
    do {
        newStateNumber = newCar.randomStateNumber();
    } while (newStateNumber == this->stateNumber || newStateNumber == other.stateNumber);

    newCar.setStateNumber(newStateNumber);

    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());

    if (!combinedThings.empty()) {
        sort(combinedThings.begin(), combinedThings.end());
        auto last = unique(combinedThings.begin(), combinedThings.end());
        combinedThings.erase(last, combinedThings.end());
    }

    newCar.SetThings(combinedThings);

    // Дополнительные параметры
    newCar.fuel = min(this->fuel, other.fuel);
    newCar.fuelConsumption = max(this->fuelConsumption, other.fuelConsumption);

    cout << "Создан новый автомобиль (оператор -)!" << endl;
    return newCar;
}

Car Car::operator/(const Car& other) const {
    Car newCar;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 1);

    if (dist(gen) == 0) {
        newCar.brand = this->brand;
        cout << "Выбрана марка первого автомобиля: " << this->brand << endl;
    }
    else {
        newCar.brand = other.brand;
        cout << "Выбрана марка второго автомобиля: " << other.brand << endl;
    }

    string newStateNumber;
    do {
        newStateNumber = newCar.randomStateNumber();
    } while (newStateNumber == this->stateNumber || newStateNumber == other.stateNumber);

    newCar.setStateNumber(newStateNumber);

    vector<string> commonThings;
    for (const auto& item1 : this->things) {
        for (const auto& item2 : other.things) {
            if (item1 == item2) {
                commonThings.push_back(item1);
                break;
            }
        }
    }

    if (!commonThings.empty()) {
        sort(commonThings.begin(), commonThings.end());
        auto last = unique(commonThings.begin(), commonThings.end());
        commonThings.erase(last, commonThings.end());
    }

    newCar.SetThings(commonThings);

    // Дополнительные параметры
    newCar.fuel = 0; // При делении топливо не копируется
    newCar.fuelConsumption = (this->fuelConsumption + other.fuelConsumption) / 2;

    cout << "Создан новый автомобиль (оператор /)!" << endl;
    return newCar;
}

// ========== СКРУЧИВАНИЕ ПРОБЕГА ==========
void Car::updateMileage(int km) {
    if (km > 0) {
        if (mileage - km < 0) {
            throw invalid_argument("Пробег должен быть неотрицательным");
        }
    }
    if (km < 0) {
        throw invalid_argument("Скрутка на отрицательный пробег невозможна");
    }

    mileage -= km;
    cout << "Пробег скручен на " << km << " км. Новый пробег: " << mileage << " км" << endl;
}

// ========== ДРУЖЕСТВЕННАЯ ФУНКЦИЯ ==========
void transferCarBetweenWorkshops(Car& car, AutoWorkshop& from, AutoWorkshop& to, int distance) {
    cout << "\n[transferCarBetweenWorkshops] Начинаем перегон автомобиля..." << endl;

    // Проверяем, прикреплена ли машина к мастерской 'from'
    if (!from.isCarAttached(&car)) {
        throw runtime_error("Машина не прикреплена к мастерской 'from'");
    }

    cout << "Перегон из '" << from.getAddress()
        << "' в '" << to.getAddress()
        << "' на расстояние " << distance << " км" << endl;

    // Проверяем возможность поездки
    if (!car.canTravel(distance)) {
        throw runtime_error("Недостаточно топлива для перегона!");
    }

    // Совершаем поездку
    car.travel(distance);

    // Открепляем от старой мастерской
    from.detachCar(&car);

    // Прикрепляем к новой мастерской
    to.attachCar(&car);

    // Устанавливаем новый адрес мастерской для машины
    car.setCurrentWorkshop(to.getAddress());

    cout << "[transferCarBetweenWorkshops] Перегон завершен успешно!" << endl;
    cout << "Автомобиль теперь прикреплен к: " << car.getCurrentWorkshop() << endl;
}