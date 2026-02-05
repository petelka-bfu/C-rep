#include "Header1.h"
#include "CarLibrary.hpp"
#include <iostream>
#include <vector>

int main() {
    std::cout << "=== ТЕСТ БИБЛИОТЕКИ ===" << std::endl;

    try {
        // 1. Создаем автомобили
        Car car1("Toyota", "Camry", "12345678901234567", "A123BC",
            "Тойота Центр", "Стандартная", 50000, 50, 8, 60, {});

        // 2. Создаем магнитолы
        Magnitola magn1("Sony XAV-AX100", "Сенсорный экран", 35000);
        Magnitola magn2("Pioneer", "Беспроводная", 25000);

        // 3. Создаем автомастерскую
        std::vector<Magnitola> magnitols = { magn1, magn2 };
        AutoMaster master("ул. Ленина, 10", magnitols);

        // 4. Прикрепляем автомобиль
        master.attachCar(&car1);

        // 5. Показываем до установки
        std::cout << "До установки магнитолы: " << car1.getCar_stereo() << std::endl;

        // 6. Устанавливаем магнитолу
        if (master.installMagnitola("A123BC", 0)) {
            std::cout << "Магнитола успешно установлена!" << std::endl;
        }

        // 7. Показываем после установки
        std::cout << "После установки: " << car1.getCar_stereo() << std::endl;

        // 8. Полная информация
        car1.displayInfo();

    }
    catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}