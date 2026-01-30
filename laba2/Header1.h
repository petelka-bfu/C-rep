
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>

class Car
{
private:
    std::string brand;
    std::string state_number;
    std::vector<std::string> things;

protected:
    std::string model;
    std::string VIN;
    int mileage;

    // Вспомогательные методы проверки
    bool isValidVINChar(char c) const;
    bool isValidStateNumberChar(char c) const;
    bool isLetter(char c) const;

public:
    // Конструкторы и деструктор
    Car();
    Car(const Car& other);
    Car(std::string br, std::string m, std::string V, std::string st_n, int mil, std::vector<std::string> th);
    ~Car();

    // Геттеры
    std::string getBrand() const;
    std::string getModel() const;
    std::string get_VIN() const;
    std::string getState_number() const;
    int getMileage() const;

    // Сеттеры
    void SetThings(const std::vector<std::string>& thing);
    void setVIN(const std::string& newVIN);
    void setStateNumber(const std::string& newNumber);

    // Методы
    void displayInfo() const;
    void updateMileage(int prob);
    std::string RandomStateNumber();

    // Операторы
    Car operator+(const Car& other) const;
    Car& operator=(const Car& other); // Можно добавить позже

    // Геттер для things (нужен для оператора +)
    std::vector<std::string> getThings() const;
};

#endif // CAR_H