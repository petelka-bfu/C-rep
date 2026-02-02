#include <iostream>
#include <vector>
#include "Header2.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");

    try {
        cout << "Введите данные автомобиля : марка, модель, номер кузова, гос номер, пробег" << endl;
        string br, mo, vin, st;
        int mi;
        cin >> br >> mo >> vin >> st >> mi;
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
        Car car(br, mo, vin, st, mi, items);
        car.displayInfo();

        Car car1("BMW","M5","01234567891234567", "Б777ББ77", 12000, {"be","me","bsd"});
        /*
        * cout << "проверка блока try catch c ошибкой длины гос номера" << endl;
        // 1. Проверка ошибки длины гос номера
        try {
            Car car1("Test", "Model", "12345678901234567", "A12", 1000, {"asd","wasd","rea"});
        }
        catch (const length_error& e) {
            cout << "Поймано length_error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Поймано invalid_argument: " << e.what() << endl;
        }
        */
        int b;
        cout << "Для продолжения введите любое число" << endl;
        cin >> b;


        //оператор +
        Car car2 = car + car1;
        car2.displayInfo();
        // 2. Проверка ошибки длины номера кузова
        /*
        cout << "проверка блока try catch c ошибкой длины номера кузова" << endl;
        try {
            Car car2("Test", "Model", "123", "A123BC", 1000, { "asd","wasd","rea" });
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
        */
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
