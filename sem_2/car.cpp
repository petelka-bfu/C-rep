#include "Header2.h"

using namespace std;

Car::Car() : brand("Неизвестно"), model("Неизвестно"), VIN("00000000000000000"),
state_number("A777AA777"), mileage(0)
{
    cout << "конструктор по умолчанию" << endl;
}

Car::Car(const Car& other) : brand(other.brand), model(other.model), VIN(other.VIN),
state_number(other.state_number), mileage(other.mileage), things(other.things)
{
}

Car::Car(string br, string m, string V, string st_n, int mil, vector<string> th) {
    brand = br;
    model = m;
    mileage = mil;
    setVIN(V);
    setStateNumber(st_n);
    SetThings(th);
    cout << "параметризированный конструктор" << endl;
}

Car::~Car() {
    cout << "Деструктор" << endl;
}

string Car::getBrand() const { return brand; }
string Car::getModel() const { return model; }
string Car::get_VIN() const { return VIN; }
string Car::getState_number() const { return state_number; }
int Car::getMileage() const { return mileage; }
vector<string> Car::getThings() const { return things; }

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

string Car::RandomStateNumber() const {
    random_device rd;
    mt19937 gen(rd());

    string letters = "ABCEHKMOPTXY";
    if (letters.empty()) {
        throw runtime_error("Letters string is empty");
    }

    string result;
    uniform_int_distribution<int> letterDist(0, static_cast<int>(letters.size()) - 1);

    // 1 буква
    result += letters[letterDist(gen)];

    // 3 цифры
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

    // 2 буквы
    result += letters[letterDist(gen)];
    result += letters[letterDist(gen)];

    // регион
    uniform_int_distribution<int> regionDist(1, 99);
    int region = regionDist(gen);
    if (region < 10) {
        result += "0" + to_string(region);
    }
    else {
        result += to_string(region);
    }

    return result; // Пример: "А123БВ77"
}


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

void Car::displayInfo() const {
    cout << "Информация об автомобиле" << endl;
    cout << "Марка: " << brand << endl;
    cout << "Модель: " << model << endl;  
    cout << "Номер кузова: " << VIN << endl; 
    cout << "Пробег: " << mileage << " км" << endl; 
    cout << "Гос. номер: " << state_number << endl;
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
// операторы
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

    // Генерируем уникальный номер
    string newStateNumber;
    int attempts = 0;
    do {
        newStateNumber = newCar.RandomStateNumber();
        cout << "Сгенерирован номер: " << newStateNumber << " (длина: " << newStateNumber.length() << ")" << endl;
        attempts++;
        if (attempts > 10) {
            // Запасной вариант
            newStateNumber = "A111AA77";
            break;
        }
    } while (newStateNumber == this->state_number || newStateNumber == other.state_number);

    newCar.setStateNumber(newStateNumber);

    // Объединяем вещи
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
    Car newCar; // Все поля по умолчанию

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

    // Объединяем вещи и удаляем дубликаты
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
    Car newCar; // Все поля по умолчанию

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

    // Находим общие вещи
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

//Конец операторов
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

