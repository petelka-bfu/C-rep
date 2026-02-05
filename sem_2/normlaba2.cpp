#include <iostream>
#include <vector>
#include "Header1.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    try {
        cout << "Введите данные автомобиля: марка, модель, номер кузова, гос номер, пробег, сервис, "
            << "марка магнитолы, количество топлива в литрах, РАСХОД ТОПЛИВА (л/100км), ОБЪЕМ БЕНЗОБАКА" << endl;
        string br, mo, vin, st, ster, serv;
        int mi, fuel, fuel_cap, fuel_ta;
        cin >> br >> mo >> vin >> st >> mi >> serv >> ster >> fuel >> fuel_cap >> fuel_ta;

        cout << "сколько вещей в багажнике?" << endl;
        int a;
        cin >> a;
        vector<string> items;
        items.reserve(a);

        if (a != 0) {
            cout << "Введите все вещи лежащие в багажнике" << endl;
        }
        for (int i = 0; i < a; i++) {
            string item;
            cin >> item;
            items.push_back(item);
        }

        Car car(br, mo, vin, st, serv, ster, mi, fuel, fuel_cap, fuel_ta, items);
        car.displayInfo();

        Car car1("BMW", "M5", "01234567891234567", "B777BB77", "Auto", "Basix",
            12000, 50, 4, 60, { "be", "me", "bsd" });

        int b;
        cout << "Для продолжения введите любое число" << endl;
        cin >> b;

        // оператор +
        Car car2 = car + car1;
        car2.displayInfo();

        try {
            car.updateMileage(1000);
        }
        catch (const invalid_argument& e) {
            cout << "Поймано invalid_argument: " << e.what() << endl;
        }
    }
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
