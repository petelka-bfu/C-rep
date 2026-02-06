#include <iostream>
#include <vector>
#include "Header1.h"
#include "autoworkshop_lib.hpp"

using namespace std;

void testBasicFunctionality() {
    cout << "\n=== ТЕСТ 1: БАЗОВАЯ ФУНКЦИОНАЛЬНОСТЬ ===" << endl;

    try {
        // Создаем простой автомобиль
        Car car1("Toyota", "Camry", "JTDKB20U123456789", "A123BC777",
            15000, 40, 60, 8, { "документы", "аптечка" });

        car1.displayInfo();

        // Тест заправки
        cout << "\n--- Тест заправки ---" << endl;
        car1.refuel(10);

        // Тест поездки
        cout << "\n--- Тест поездки ---" << endl;
        if (car1.canTravel(100)) {
            car1.addKilometers(100);
        }

        // Тест скрутки пробега
        cout << "\n--- Тест скрутки пробега ---" << endl;
        car1.updateMileage(50);

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void testLibraryIntegration() {
    cout << "\n\n=== ТЕСТ 2: ИНТЕГРАЦИЯ С БИБЛИОТЕКОЙ ===" << endl;

    try {
        // Создаем мастерские
        AutoWorkshop workshop1("ул. Ленина, 10");
        AutoWorkshop workshop2("пр. Мира, 25");

        // Создаем магнитолы
        CarStereo stereo1("Sony XAV-AX100", "Premium система", 35000);
        CarStereo stereo2("Pioneer Basic", "Бюджетный вариант", 12000);

        workshop1.addStereo(stereo1);
        workshop2.addStereo(stereo2);

        // Создаем автомобили
        Car car1("BMW", "X5", "WBAFR71050LN12345", "B777BB777",
            80000, 50, 80, 12, { "запаска", "домкрат" });

        Car car2("Audi", "A6", "WAUZZZ4L8BD123456", "C123CC777",
            45000, 60, 70, 9, { "документы", "аптечка", "одеяло" });

        // Прикрепляем к мастерским
        workshop1.attachCar(&car1);
        workshop2.attachCar(&car2);

        // Устанавливаем магнитолы
        car1.setCarStereo(&stereo1);
        car2.setCarStereo(&stereo2);

        // Отображаем информацию
        car1.displayInfo();
        car2.displayInfo();

        workshop1.displayInfo();
        workshop2.displayInfo();

        // Тест операторов
        cout << "\n--- Тест операторов ---" << endl;
        Car car3 = car1 + car2;
        car3.displayInfo();

    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void testCarTransfer() {
    cout << "\n\n=== ТЕСТ 3: ПЕРЕГОН АВТОМОБИЛЯ ===" << endl;

    try {
        AutoWorkshop workshop1("Сервис 'Северный'");
        AutoWorkshop workshop2("Сервис 'Южный'");

        Car car("Volkswagen", "Golf", "WVWZZZ1JZ3W123456", "E123EE777",
            30000, 60, 55, 7, { "трос", "фонарик" });

        workshop1.attachCar(&car);
        car.setCurrentWorkshop(workshop1.getAddress());
        car.refuel(40); // Заправляем для поездки

        cout << "До перегона:" << endl;
        car.displayInfo();

        // Перегон
        transferCarBetweenWorkshops(car, workshop1, workshop2, 200);

        cout << "\nПосле перегона:" << endl;
        car.displayInfo();

    }
    catch (const exception& e) {
        cout << "Ошибка при перегоне: " << e.what() << endl;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");

    cout << "ТЕСТИРОВАНИЕ АВТОМОБИЛЬНОЙ СИСТЕМЫ" << endl;;

    try {
        testBasicFunctionality();
        testLibraryIntegration();
        testCarTransfer();
        cout << "ВСЕ ТЕСТЫ УСПЕШНО ЗАВЕРШЕНЫ!" << endl;

    }
    catch (...) {
        cout << "\n!!! КРИТИЧЕСКАЯ ОШИБКА !!!" << endl;
        return 1;
    }

    int a;
    cout << "Это конец моей лабы на которую я убил 8 часов, сейчас время 3 ночи. я очень надеюсь что лаба будет засчитана иначе я зря 9 раз создавал проект заново" << endl;
    cout << "Лаба мне очень понравилась, тема опрделенно интересная, но я зря попросил доп потому что из за него у меня вместо 3 часов вышло 8, сложность лабы оцениваю на 9/10, я ментально умер(" << endl;
    cin >> a;


    return 0;
}