#include "Header1.h"

using namespace std;

// Конструктор по умолчанию
Car::Car() : brand("Неизвестно"), model("Неизвестно"), VIN("00000000000000000"),
state_number("A777AA777"), mileage(0)
{
    cout << "конструктор по умолчанию" << endl;
}

// Конструктор копирования
Car::Car(const Car& other) : brand(other.brand), model(other.model), VIN(other.VIN),
state_number(other.state_number), mileage(other.mileage), things(other.things)
{
}

// Параметризированный конструктор
Car::Car(string br, string m, string V, string st_n, int mil, vector<string> th) {
    brand = br;
    model = m;
    mileage = mil;
    setVIN(V);
    setStateNumber(st_n);
    SetThings(th);
    cout << "параметризированный конструктор" << endl;
}

// Деструктор
Car::~Car() {
    cout << "Деструктор" << endl;
}

// Геттеры
string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
string Car::get_VIN() const { return VIN; }
string Car::getState_number() const { return state_number; }
int Car::getMileage() const { return mileage; }
vector<string> Car::getThings() const { return things; }

// Вспомогательные методы проверки
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
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
    if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) return true;
    return false;
}

// Метод генерации случайного госномера
string Car::RandomStateNumber() {
    random_device rd;
    mt19937 gen(rd());

    string letters = "ABCEHKMOPTXYАВСЕНКМОРТХУ";
    string result;

    uniform_int_distribution<int> letterDist(0, letters.size() - 1);
    result += letters[letterDist(gen)];

    uniform_int_distribution<int> digitDist(0, 9);
    for (int i = 0; i < 3; i++) {
        result += to_string(digitDist(gen))[0];
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

// Оператор сложения
Car Car::operator+(const Car& other) const {
    Car newCar;

    // 1. Случайный выбор марки
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

    // 2. Случайный выбор модели
    uniform_int_distribution<int> modelDist(0, 1);
    if (modelDist(gen) == 0) {
        newCar.model = this->model;
    }
    else {
        newCar.model = other.model;
    }

    // 3. Генерация уникального VIN (комбинация двух VIN)
    string newVIN = this->VIN.substr(0, 8) + other.VIN.substr(8, 9);
    newCar.setVIN(newVIN);

    // 4. Генерация уникального госномера
    string newStateNumber;
    do {
        newStateNumber = RandomStateNumber();
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);

    newCar.setStateNumber(newStateNumber);

    // 5. Средний пробег
    newCar.mileage = (this->mileage + other.mileage) / 2;

    // 6. Объединение вещей
    vector<string> combinedThings = this->things;
    combinedThings.insert(combinedThings.end(), other.things.begin(), other.things.end());
    newCar.SetThings(combinedThings);

    cout << "Создан новый автомобиль!" << endl;
    return newCar;
}

// Оператор присваивания (дополнительно)
Car& Car::operator=(const Car& other) {
    if (this != &other) { // Проверка на самоприсваивание
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

// Сеттер для вещей
void Car::SetThings(const vector<string>& thing) {
    things = thing;
}

// Сеттер для VIN
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

// Сеттер для госномера
void Car::setStateNumber(const string& newNumber) {
    if (newNumber.empty()) {
        throw invalid_argument("Государственный номер не может быть пустым");
    }

    if (newNumber.length() < 6 || newNumber.length() > 9) {
        throw length_error("Государственный номер должен содержать от 6 до 9 символов");
    }

    // Проверка, что в номере есть хотя бы одна буква и одна цифра
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

// Метод отображения информации
void Car::displayInfo() const {
    cout << "Информация об автомобиле" << endl;
    cout << "Марка: " << brand << endl;
    cout << "Модель: " << model << endl;
    cout << "Номер кузова: " << VIN << endl;
    cout << "Гос. номер: " << state_number << endl;
    cout << "Пробег: " << mileage << " км" << endl;
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

// Метод обновления пробега
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