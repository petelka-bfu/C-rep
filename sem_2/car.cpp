#include "Header1.h"
using namespace std;

// КОНСТРУКТОРЫ И ДЕСТРУКТОР
Car::Car() : brand("Неизвестно"), model("Неизвестно"), VIN("00000000000000000"),
state_number("A777AA777"), mileage(0),things({}),fuel_cons(0),servis("Неизвестно"),car_stereo("Магнитолка"),fuel(0),fuel_tank_cap(0)
{
    cout << "конструктор по умолчанию" << endl;
}

Car::Car(const Car& other) : brand(other.brand), model(other.model), VIN(other.VIN),
state_number(other.state_number), mileage(other.mileage), things(other.things),
fuel_cons(other.fuel_cons),fuel(other.fuel),servis(other.servis),car_stereo(other.car_stereo),fuel_tank_cap(other.fuel_tank_cap)
{
}



Car::Car(string br, string m, string V, string st_n,
    string serv, string ster, int mil, int fu,
    int fu_cap, int fu_tan, vector<string> th) 
{
    brand = br;
    model = m;
    servis = serv;
    car_stereo = ster;
    mileage = mil;
    fuel = fu;
    fuel_cons = fu_cap;
    fuel_tank_cap = fu_tan;

    setVIN(V);
    setStateNumber(st_n);
    SetThings(th);

    cout << "параметризированный конструктор" << endl;
}

Car::~Car() {
    cout << "Деструктор" << endl;
}


//ГЕТТЕРЫ
string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
string Car::get_VIN() const { return VIN; }
string Car::getState_number() const { return state_number; }
string Car::getServis() const { return servis; }
string Car::getCar_stereo() const { return car_stereo; }
int Car::getFuel() const { return fuel; }
int Car::getMileage() const { return mileage; }
int Car::getFuel_cons()const { return fuel_cons; }
vector<string> Car::getThings() const { return things; }


//БУЛЕВЫЕ
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



//РАНДОМ
string Car::RandomStateNumber() const {
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


//СЕТТЕРЫ
void Car::SetThings(const vector<string>& thing) {
    things = thing;
}

void Car::setVIN(const string& newVIN) {
    if (newVIN.length() != 17) {
        throw length_error("Длина должна быть ровно 17 символов");
    }

    for (char c : newVIN) {
        if (!isValidVINChar(c)) {
            throw invalid_argument("Найден недопустимый символ");
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

    state_number = newNumber;
}


//ОТОБРАЖЕНИЕ
void Car::displayInfo() const {
    cout << "Информация об автомобиле" << endl;
    cout << "Марка: " << brand << endl;
    cout << "Модель: " << model << endl;  
    cout << "Номер кузова: " << VIN << endl; 
    cout << "Гос. номер: " << state_number << endl;
    cout << "Магнитола: " << car_stereo << endl;
    cout << "Сервис: " << servis << endl;
    cout << "Пробег: " << mileage << " км" << endl;
    cout << "Количество топлива: " << fuel << endl;
    cout << "Расход топлива: " << fuel_cons << endl;
    cout << "Объем бензобака: " << fuel_tank_cap << endl;

    



    cout << "Список вещей в багажнике:" << endl;

    if (things.empty()) {
        cout << "  Багажник пуст" << endl;
    }
    else {
        for (size_t i = 0; i < things.size(); ++i) {
            cout << "  " << i + 1 << ". " << things[i] << endl;
        }
    }
    cout << endl;
}


// ОПЕРАТОРЫ
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
        newStateNumber = newCar.RandomStateNumber();
        cout << "Сгенерирован номер: " << newStateNumber << " (длина: " << newStateNumber.length() << ")" << endl;
        attempts++;
        if (attempts > 10) {
            newStateNumber = "A111AA77";
            break;
        }
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);

    newCar.setStateNumber(newStateNumber);

    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());
    newCar.SetThings(combinedThings);

    cout << "Создан новый автомобиль (оператор +)!" << endl;
    return newCar;
}

Car& Car::operator=(const Car& other) {
    if (this != &other) {
        brand = other.brand;
        model = other.model;
        VIN = other.VIN;
        state_number = other.state_number;
        mileage = other.mileage;
        things = other.things;
        cout << "Выполнено присваивание" << endl;
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
        newStateNumber = newCar.RandomStateNumber();
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);

    newCar.setStateNumber(newStateNumber);

    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());

    if (!combinedThings.empty()) {
        sort(combinedThings.begin(), combinedThings.end());
        auto last = unique(combinedThings.begin(), combinedThings.end());
        combinedThings.erase(last, combinedThings.end());
    }

    newCar.SetThings(combinedThings);

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
        newStateNumber = newCar.RandomStateNumber();
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);

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

    cout << "Создан новый автомобиль (оператор /)!" << endl;
    return newCar;
}


//ПРОБЕГ
void Car::updateMileage(int prob) {
    if (prob > 0) {
        if (mileage - prob < 0) {
            throw invalid_argument("Пробег должен быть неотрицательным");
        }
    }
    if (prob < 0)
    {
        throw invalid_argument("Скрутка на отрицательный пробег невозможна");
    }

    mileage -= prob;
}
//Замена магнитолы
void Car::Stereo_change()
{
    string NewSter;
    cout << "Введите новую магнитолу" << endl;
    car_stereo = NewSter;
}
//Френд функция
void distillation(Car& car) {
    cout << "Введите название нового сервиса и расстояние до него" << endl;
    string NewServ;
    int distance;
    cin >> NewServ >> distance;
    if (car.fuel * car.fuel_cons < distance) {
        throw out_of_range("Не хватает топлива, ищите заправку");
    }
    else {
        car.mileage += distance;
        car.fuel -= distance / car.fuel_cons;
        car.servis = NewServ;
    }

}
//Заправка
void Car::refueling() 
{
    int bonus_fuel;
    cout << "Введите сколько литров заправленно" << endl;
    cin >> bonus_fuel;
    if (bonus_fuel > 0) {
        if (fuel + bonus_fuel > fuel_tank_cap) {
            throw out_of_range("Слишком много топлива, вы пролили его и взорвались :)");
        }
        else {
            fuel += bonus_fuel;
        }
    }
    else {
        throw invalid_argument("Как ты заправил отрицательное количество топлива?");
    }

}
