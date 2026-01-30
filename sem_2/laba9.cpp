#include <iostream>
#include <string>
#include <stdexcept>
#include <cctype>
using namespace std;

class Car
{
private:
    string brand;
    string model;
    string VIN;
    string state_number;
    int mileage;

protected:
    bool isValidVINChar(char c) const {
        return isdigit(c) || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }
    
    bool isValidStateNumberChar(char c) const {
        if (c >= '0' && c <= '9') return true;
        if (c >= 'A' && c <= 'Z') return true;
        if (c >= 'a' && c <= 'z') return true;
        if (c >= 'А' && c <= 'Я') return true;
        if (c >= 'а' && c <= 'я') return true;
        return false;
    }
    
    bool isLetter(char c) const {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) return true;
        if ((c >= 'А' && c <= 'Я') || (c >= 'а' && c <= 'я')) return true;
        return false;
    }

public:
    Car() : brand("Неизвестно"), model("Неизвестно"), VIN("00000000000000000"),
        state_number("A777AA777"), mileage(0)
    {
        cout << "конструктор по умолчанию" << endl;
    }

    Car(const Car& other) : brand(other.brand), model(other.model), VIN(other.VIN),
        state_number(other.state_number), mileage(other.mileage)
    {
    }

    Car(string br, string m, string V, string st_n, int mil) {
        brand = br;
        model = m;
        mileage = mil;
        setVIN(V);
        setStateNumber(st_n);
        cout << "параметризированный конструктор" << endl;
    }

    string getBrand()const { return brand; }
    string getModel()const { return model; }
    string get_VIN()const { return VIN; }
    string getState_number()const { return state_number; }
    int getMileage()const { return mileage; }

    ~Car() {
        cout << "Деструктор" << endl;
    }

    void setVIN(const string& newVIN) {
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

    void setStateNumber(const string& newNumber) {
        if (newNumber.empty()) {
            throw invalid_argument("Государственный номер не может быть пустым");
        }

        if (newNumber.length() < 6 || newNumber.length() > 9) {
            throw length_error("Государственный номер должен содержать от 6 до 9 символов");
        }

        int letter_positions[] = { 0, 3, 4 };

        for (int pos : letter_positions) {
            if (pos < newNumber.length()) {
                char c = newNumber[pos];
                if (!isLetter(c)) {
                    throw invalid_argument("Была введена цифра вместо буквы");
                }
            }
        }

        for (char c : newNumber) {
            if (!isValidStateNumberChar(c)) {
                throw invalid_argument("Государственный номер содержит недопустимый символ: '" +
                    string(1, c) + "'");
            }
        }

        state_number = newNumber;
    }

    void displayInfo() const {
        cout << "Информация об автомобиле" << endl;
        cout << "Марка: " << brand << endl;
        cout << "Модель: " << model << endl;
        cout << "Номер кузова: " << VIN << endl;
        cout << "Гос. номер: " << state_number << endl;
        cout << "Пробег: " << mileage << " км" << endl;
    }

    void updateMileage(int prob) {
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
};

int main()
{
    setlocale(LC_ALL, "RUS");

    try {
        cout << "Введите данные автомобиля : марка, модель, номер кузова, гос номер, пробег" << endl;
        string br, mo, vin, st;
        int mi;
        cin >> br >> mo >> vin >> st >> mi;

        Car car(br, mo, vin, st, mi);
        car.displayInfo();

        cout << "проверка блока try catch c ошибкой длины гос номера" << endl;

        // 1. Проверка ошибки длины гос номера
        try {
            Car car1("Test", "Model", "12345678901234567", "A12", 1000);
        }
        catch (const length_error& e) {
            cout << "Поймано length_error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Поймано invalid_argument: " << e.what() << endl;
        }

        int a;
        cout << "Для продолжения введите любое число" << endl;
        cin >> a;

        cout << "проверка блока try catch c ошибкой длины номера кузова" << endl;

        // 2. Проверка ошибки длины номера кузова
        try {
            Car car2("Test", "Model", "123", "A123BC", 1000);
        }
        catch (const invalid_argument& e) {
            cout << "Поймано invalid_argument: " << e.what() << endl;
        }
        catch (const length_error& e) {
            cout << "Поймано length_error: " << e.what() << endl;
        }

        cout << "Для продолжения введите любое число" << endl;
        cin >> a;

        cout << "проверка блока try catch c ошибкой отрицательного пробега" << endl;

        // 3. Проверка ошибки отрицательного пробега
        try {
            car.updateMileage(1000);
        }
        catch (const invalid_argument& e) {
            cout << "Поймано invalid_argument: " << e.what() << endl;
        }
    }
    // Глобальный обработчик для исключений при создании первого объекта
    catch (const length_error& e) {
        cout << "Ошибка при создании автомобиля (length_error): " << e.what() << endl;
        return 1;
    }
    catch (const invalid_argument& e) {
        cout << "Ошибка при создании автомобиля (invalid_argument): " << e.what() << endl;
        return 1;
    }
    catch (const exception& e) {
        cout << "Ошибка при создании автомобиля: " << e.what() << endl;
        return 1;
    }

    return 0;
}
