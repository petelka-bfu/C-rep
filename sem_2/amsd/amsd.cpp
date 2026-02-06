#include <iostream>
#include <vector>
#include "Header1.h"
#include "autoworkshop_lib.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    try {
        cout << "=== ТЕСТИРОВАНИЕ БИБЛИОТЕКИ АВТОМАСТЕРСКОЙ ===" << endl;

        // 1. Создаем автомастерские
        AutoWorkshop workshop1("ул. Ленина, 10");
        AutoWorkshop workshop2("пр. Мира, 25");

        // 2. Создаем магнитолы
        CarStereo stereo1("Sony XAV-AX100", "Мультимедийная система с Apple CarPlay", 35000);
        CarStereo stereo2("Pioneer MVH-S320BT", "Bluetooth магнитола с USB", 12000);
        CarStereo stereo3("Kenwood DMX-5020BT", "2-DIN дисплей с навигацией", 45000);

        // 3. Добавляем магнитолы в мастерские
        workshop1.addStereo(stereo1);
        workshop1.addStereo(stereo2);
        workshop2.addStereo(stereo3);

        cout << "\n=== СОЗДАНИЕ АВТОМОБИЛЕЙ ===" << endl;
        cout << "Введите данные автомобиля: марка, модель, VIN, гос номер, пробег" << endl;
        cout << "Пример: Toyota Camry JTDKB20U123456789 A123BC777 15000" << endl;

        string brand, model, vin, stateNum;
        int mileage;

        cin >> brand >> model >> vin >> stateNum >> mileage;

        // Проверка ввода
        if (cin.fail()) {
            throw runtime_error("Ошибка ввода данных");
        }

        // Создаем вектор вещей
        vector<string> things = { "документы", "аптечка", "трос" };

        // Создаем автомобиль БЕЗ магнитолы (nullptr)
        Car car1(brand, model, vin, stateNum,
            workshop1.getAddress(), nullptr, mileage,
            50,  // топливо
            60,  // объем бака
            8,   // расход
            things);

        car1.displayInfo();

        // Прикрепляем автомобиль к мастерской
        workshop1.attachCar(&car1);

        // Тестируем заправку
        cout << "\n=== ТЕСТ ЗАПРАВКИ ===" << endl;
        car1.refuel(20);

        // Тестируем поездку
        cout << "\n=== ТЕСТ ПОЕЗДКИ ===" << endl;
        if (car1.canTravel(100)) {
            car1.travel(100);
        }
        else {
            cout << "Недостаточно топлива для поездки" << endl;
        }

        // Тестируем установку магнитолы
        cout << "\n=== ТЕСТ УСТАНОВКИ МАГНИТОЛЫ ===" << endl;
        car1.setInstalledStereo(&stereo1);

        // Тестируем операторы
        cout << "\n=== ТЕСТ ОПЕРАТОРОВ ===" << endl;
        Car car2("BMW", "X5", "WBAFR71050LN12345", "B777BB777",
            workshop2.getAddress(), &stereo3, 80000, 30, 80, 12,
            { "запаска", "домкрат" });

        workshop2.attachCar(&car2);
        car2.displayInfo();

        // Тест оператора +
        cout << "\n=== ТЕСТ ОПЕРАТОРА + ===" << endl;
        Car car3 = car1 + car2;
        car3.displayInfo();

        // Тест перегона между сервисами
        cout << "\n=== ТЕСТ ПЕРЕГОНА МЕЖДУ СЕРВИСАМИ ===" << endl;
        try {
            // Заправляем для поездки
            car1.refuel(50);

            // Перегоняем машину
            transferCarBetweenWorkshops(car1, workshop1, workshop2, 50);
        }
        catch (const exception& e) {
            cout << "Ошибка при перегоне: " << e.what() << endl;
        }

        // Отображаем информацию о мастерских
        cout << "\n=== ИНФОРМАЦИЯ О МАСТЕРСКИХ ===" << endl;
        workshop1.displayInfo();
        workshop2.displayInfo();

        cout << "\n=== ТЕСТ ЗАВЕРШЕН УСПЕШНО ===" << endl;

    }
    catch (const bad_alloc& e) {
        cout << "Ошибка выделения памяти: " << e.what() << endl;
        return 1;
    }
    catch (const length_error& e) {
        cout << "Ошибка длины: " << e.what() << endl;
        return 1;
    }
    catch (const invalid_argument& e) {
        cout << "Неверный аргумент: " << e.what() << endl;
        return 1;
    }
    catch (const out_of_range& e) {
        cout << "Выход за границы: " << e.what() << endl;
        return 1;
    }
    catch (const exception& e) {
        cout << "Общая ошибка: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cout << "Неизвестная ошибка!" << endl;
        return 1;
    }

    // Пауза для просмотра результатов
    cout << "\nНажмите Enter для выхода...";
    cin.ignore();
    cin.get();

    return 0;
}