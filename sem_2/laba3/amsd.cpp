#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "Header1.h"
#include "autoworkshop_lib.hpp"

using namespace std;

// Глобальные коллекции для хранения объектов
vector<unique_ptr<Car>> cars;
vector<unique_ptr<AutoWorkshop>> workshops;
vector<CarStereo> stereos;

// Прототипы функций
void displayMainMenu();
void createNewCar();
void createNewWorkshop();
void createNewStereo();
void displayAllObjects();
void viewSpecificField();
void testOperators();
void performActionOnAll();
void performCarActions(Car& car);
void performWorkshopActions(AutoWorkshop& workshop);
void saveToFile();
void loadFromFile();
void clearAllData();

// Вспомогательные функции
Car* selectCar(const string& prompt);
AutoWorkshop* selectWorkshop(const string& prompt);
CarStereo* selectStereo(const string& prompt);
void pressEnterToContinue();

int main() {
    setlocale(LC_ALL, "RUS");

    //базовые магнитолы
    stereos.push_back(CarStereo("Sony XAV-AX100", "Premium система с CarPlay", 35000));
    stereos.push_back(CarStereo("Pioneer MVH-S320BT", "Бюджетная магнитола", 12000));
    stereos.push_back(CarStereo("Kenwood Excelon", "Мощная акустика", 55000));

    //базовые мастерские
    workshops.push_back(make_unique<AutoWorkshop>("ул. Ленина, 10"));
    workshops.push_back(make_unique<AutoWorkshop>("пр. Мира, 25"));

    //базовые машины
    cars.push_back(make_unique<Car>("Toyota", "Camry", "JTDKB20U123456789",
        "A123BC777", 15000, 40, 60, 8,
        vector<string>{"документы", "аптечка"}));

    cars.push_back(make_unique<Car>("BMW", "X5", "WBAFR71050LN12345",
        "B777BB777", 80000, 50, 80, 12,
        vector<string>{"запаска", "домкрат"}));

    short choice;
    do {
        displayMainMenu();
        cout << "Выберите действие: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1: createNewCar(); break;
            case 2: createNewWorkshop(); break;
            case 3: createNewStereo(); break;
            case 4: displayAllObjects(); break;
            case 5: viewSpecificField(); break;
            case 6: testOperators(); break;
            case 7: performActionOnAll(); break;
            case 8: saveToFile(); break;
            case 9: loadFromFile(); break;
            case 10: clearAllData(); break;
            case 0: cout << "Выход из программы..." << endl; break;
            default: cout << "Неверный выбор!" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (choice != 0) {
            pressEnterToContinue();
        }

    } while (choice != 0);

    return 0;
}

void displayMainMenu() {
    cout << "\n=========================================" << endl;
    cout << "          АВТОМОБИЛЬНАЯ СИСТЕМА" << endl;
    cout << "=========================================" << endl;
    cout << "Автомобилей: " << cars.size() << endl;
    cout << "Мастерских: " << workshops.size() << endl;
    cout << "Магнитол: " << stereos.size() << endl;
    cout << "=========================================" << endl;
    cout << "1. Создать новый автомобиль" << endl;
    cout << "2. Создать новую автомастерскую" << endl;
    cout << "3. Создать новую магнитолу" << endl;
    cout << "4. Просмотреть все объекты" << endl;
    cout << "5. Посмотреть конкретное поле объекта" << endl;
    cout << "6. Проверить операторы" << endl;
    cout << "7. Выполнить действие для всех объектов" << endl;
    cout << "8. Сохранить данные в файл" << endl;
    cout << "9. Загрузить данные из файла" << endl;
    cout << "10. Очистить все данные" << endl;
    cout << "0. Выход" << endl;
    cout << "=========================================" << endl;
}

void createNewCar() {
    cout << "\n=== СОЗДАНИЕ НОВОГО АВТОМОБИЛЯ ===" << endl;

    string brand, model, vin, stateNum;
    int mileage, fuel, fuelCap, fuelCons;

    cout << "Марка: ";
    cin >> brand;
    cout << "Модель: ";
    cin >> model;
    cout << "VIN (17 символов): ";
    cin >> vin;
    cout << "Госномер: ";
    cin >> stateNum;
    cout << "Пробег (км): ";
    cin >> mileage;
    cout << "Топливо (л): ";
    cin >> fuel;
    cout << "Объем бака (л): ";
    cin >> fuelCap;
    cout << "Расход (л/100км): ";
    cin >> fuelCons;

    // Ввод вещей в багажнике
    cout << "Количество вещей в багажнике: ";
    int itemCount;
    cin >> itemCount;

    vector<string> things;
    for (int i = 0; i < itemCount; i++) {
        cout << "Вещь " << (i + 1) << ": ";
        string item;
        cin >> item;
        things.push_back(item);
    }

    try {
        auto newCar = make_unique<Car>(brand, model, vin, stateNum,
            mileage, fuel, fuelCap, fuelCons, things);

        // Выбор мастерской
        if (!workshops.empty()) {
            cout << "\nПрикрепить к мастерской? (1 - да, 0 - нет): ";
            int attachChoice;
            cin >> attachChoice;

            if (attachChoice == 1) {
                AutoWorkshop* workshop = selectWorkshop("Выберите мастерскую:");
                if (workshop) {
                    workshop->attachCar(newCar.get());
                    newCar->setCurrentWorkshop(workshop->getAddress());
                }
            }
        }

        // Выбор магнитолы
        if (!stereos.empty()) {
            cout << "Установить магнитолу? (1 - да, 0 - нет): ";
            int stereoChoice;
            cin >> stereoChoice;

            if (stereoChoice == 1) {
                CarStereo* stereo = selectStereo("Выберите магнитолу:");
                if (stereo) {
                    newCar->setCarStereo(stereo);
                }
            }
        }

        cars.push_back(move(newCar));
        cout << "Автомобиль успешно создан!" << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка при создании автомобиля: " << e.what() << endl;
        throw;
    }
}

void createNewWorkshop() {
    cout << "\n=== СОЗДАНИЕ НОВОЙ АВТОМАСТЕРСКОЙ ===" << endl;

    string address;
    cout << "Введите адрес мастерской: ";
    cin.ignore();
    getline(cin, address);

    try {
        workshops.push_back(make_unique<AutoWorkshop>(address));

        // Добавление магнитол в мастерскую
        if (!stereos.empty()) {
            cout << "Добавить магнитолы в мастерскую? (1 - да, 0 - нет): ";
            int addChoice;
            cin >> addChoice;

            if (addChoice == 1) {
                for (const auto& stereo : stereos) {
                    workshops.back()->addStereo(stereo);
                }
            }
        }

        cout << "Автомастерская успешно создана!" << endl;

    }
    catch (const exception& e) {
        cout << "Ошибка при создании мастерской: " << e.what() << endl;
        throw;
    }
}

void createNewStereo() {
    cout << "\n=== СОЗДАНИЕ НОВОЙ МАГНИТОЛЫ ===" << endl;

    string model, description;
    double price;

    cout << "Модель магнитолы: ";
    cin.ignore();
    getline(cin, model);

    cout << "Описание: ";
    getline(cin, description);

    cout << "Цена: ";
    cin >> price;

    try {
        stereos.push_back(CarStereo(model, description, price));
        cout << "Магнитола успешно создана!" << endl;

        // Добавить во все мастерские?
        if (!workshops.empty()) {
            cout << "Добавить во все мастерские? (1 - да, 0 - нет): ";
            int addToAll;
            cin >> addToAll;

            if (addToAll == 1) {
                for (auto& workshop : workshops) {
                    workshop->addStereo(stereos.back());
                }
            }
        }

    }
    catch (const exception& e) {
        cout << "Ошибка при создании магнитолы: " << e.what() << endl;
        throw;
    }
}

void displayAllObjects() {
    cout << "\n=== ВСЕ АВТОМОБИЛИ ===" << endl;
    for (size_t i = 0; i < cars.size(); i++) {
        cout << "\n[" << i + 1 << "] ";
        cars[i]->displayInfo();
    }

    cout << "\n=== ВСЕ АВТОМАСТЕРСКИЕ ===" << endl;
    for (size_t i = 0; i < workshops.size(); i++) {
        cout << "\n[" << i + 1 << "] ";
        workshops[i]->displayInfo();
    }

    cout << "\n=== ВСЕ МАГНИТОЛЫ ===" << endl;
    for (size_t i = 0; i < stereos.size(); i++) {
        cout << "\n[" << i + 1 << "] ";
        stereos[i].displayInfo();
    }
}

void viewSpecificField() {
    cout << "\n=== ПРОСМОТР КОНКРЕТНОГО ПОЛЯ ===" << endl;

    cout << "Выберите тип объекта:" << endl;
    cout << "1. Автомобиль" << endl;
    cout << "2. Автомастерская" << endl;
    cout << "3. Магнитола" << endl;
    cout << "Выбор: ";

    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice) {
    case 1: {
        Car* car = selectCar("Выберите автомобиль:");
        if (!car) return;

        cout << "\nВыберите поле для просмотра:" << endl;
        cout << "1. Марка" << endl;
        cout << "2. Модель" << endl;
        cout << "3. VIN" << endl;
        cout << "4. Госномер" << endl;
        cout << "5. Пробег" << endl;
        cout << "6. Топливо" << endl;
        cout << "7. Объем бака" << endl;
        cout << "8. Расход топлива" << endl;
        cout << "9. Текущая мастерская" << endl;
        cout << "10. Установленная магнитола" << endl;
        cout << "11. Вещи в багажнике" << endl;
        cout << "Выбор: ";

        int fieldChoice;
        cin >> fieldChoice;

        switch (fieldChoice) {
        case 1: cout << "Марка: " << car->getBrand() << endl; break;
        case 2: cout << "Модель: " << car->getModel() << endl; break;
        case 3: cout << "VIN: " << car->getVIN() << endl; break;
        case 4: cout << "Госномер: " << car->getStateNumber() << endl; break;
        case 5: cout << "Пробег: " << car->getMileage() << " км" << endl; break;
        case 6: cout << "Топливо: " << car->getFuel() << " л" << endl; break;
        case 7: cout << "Объем бака: " << car->getFuelTankCapacity() << " л" << endl; break;
        case 8: cout << "Расход: " << car->getFuelConsumption() << " л/100км" << endl; break;
        case 9: cout << "Мастерская: " << car->getCurrentWorkshop() << endl; break;
        case 10: {
            auto stereo = car->getCarStereo();
            if (stereo) {
                cout << "Магнитола: " << stereo->modelName << endl;
            }
            else {
                cout << "Магнитола не установлена" << endl;
            }
            break;
        }
        case 11: {
            auto things = car->getThings();
            cout << "Вещей в багажнике: " << things.size() << endl;
            for (size_t i = 0; i < things.size(); i++) {
                cout << "  " << i + 1 << ". " << things[i] << endl;
            }
            break;
        }
        default: cout << "Неверный выбор!" << endl;
        }
        break;
    }

    case 2: {
        AutoWorkshop* workshop = selectWorkshop("Выберите автомастерскую:");
        if (!workshop) return;

        cout << "\nВыберите поле для просмотра:" << endl;
        cout << "1. Адрес" << endl;
        cout << "2. Количество доступных магнитол" << endl;
        cout << "3. Количество прикрепленных автомобилей" << endl;
        cout << "4. Список магнитол" << endl;
        cout << "Выбор: ";

        int fieldChoice;
        cin >> fieldChoice;

        switch (fieldChoice) {
        case 1: cout << "Адрес: " << workshop->getAddress() << endl; break;
        case 2: cout << "Магнитол: " << workshop->getAvailableStereos().size() << endl; break;
        case 3: cout << "Автомобилей: " << workshop->getAttachedCars().size() << endl; break;
        case 4: {
            auto availableStereos = workshop->getAvailableStereos();
            cout << "Доступные магнитолы:" << endl;
            for (size_t i = 0; i < availableStereos.size(); i++) {
                cout << "  " << i + 1 << ". " << availableStereos[i].modelName << endl;
            }
            break;
        }
        default: cout << "Неверный выбор!" << endl;
        }
        break;
    }

    case 3: {
        CarStereo* stereo = selectStereo("Выберите магнитолу:");
        if (!stereo) return;

        cout << "\nВыберите поле для просмотра:" << endl;
        cout << "1. Модель" << endl;
        cout << "2. Описание" << endl;
        cout << "3. Цена" << endl;
        cout << "Выбор: ";

        int fieldChoice;
        cin >> fieldChoice;

        switch (fieldChoice) {
        case 1: cout << "Модель: " << stereo->modelName << endl; break;
        case 2: cout << "Описание: " << stereo->description << endl; break;
        case 3: cout << "Цена: " << stereo->price << " руб." << endl; break;
        default: cout << "Неверный выбор!" << endl;
        }
        break;
    }

    default: cout << "Неверный выбор!" << endl;
    }
}

void testOperators() {
    cout << "\n=== ТЕСТИРОВАНИЕ ОПЕРАТОРОВ ===" << endl;

    if (cars.size() < 2) {
        cout << "Нужно как минимум 2 автомобиля для тестирования операторов!" << endl;
        return;
    }

    cout << "Выберите оператор:" << endl;
    cout << "1. operator+ (объединение вещей)" << endl;
    cout << "2. operator- (уникальные вещи первого авто)" << endl;
    cout << "3. operator/ (общие вещи)" << endl;
    cout << "Выбор: ";

    int opChoice;
    cin >> opChoice;

    Car* car1 = selectCar("Выберите первый автомобиль (от него возьмем все параметры кроме марки и вещей):");
    if (!car1) return;

    Car* car2 = selectCar("Выберите второй автомобиль (только для выбора марки и работы с вещами):");
    if (!car2) return;

    try {
        Car result;
        string operationName;
        string operationDescription;

        switch (opChoice) {
        case 1:
            cout << "\n=== ОПЕРАТОР + ===" << endl;
            operationName = "объединения вещей";
            operationDescription = "Марка - случайная, госномер - новый, вещи - объединенные, остальное - от первого авто";
            result = *car1 + *car2;
            break;

        case 2:
            cout << "\n=== ОПЕРАТОР - ===" << endl;
            operationName = "уникальных вещей первого авто";
            operationDescription = "Марка - случайная, госномер - новый, вещи - уникальные из первого авто, остальное - от первого авто";
            result = *car1 - *car2;
            break;

        case 3:
            cout << "\n=== ОПЕРАТОР / ===" << endl;
            operationName = "общих вещей";
            operationDescription = "Марка - случайная, госномер - новый, вещи - общие, остальное - от первого авто";
            result = *car1 / *car2;
            break;

        default:
            cout << "Неверный выбор оператора!" << endl;
            return;
        }

        cout << "\nЛогика операции " << operationName << ":" << endl;
        cout << operationDescription << endl;
        cout << "\nРезультат:" << endl;
        result.displayInfo();

        cout << "\nСохранить результат как новый автомобиль? (1 - да, 0 - нет): ";
        int saveChoice;
        cin >> saveChoice;

        if (saveChoice == 1) {

            auto newCar = make_unique<Car>(
                result.getBrand(),
                result.getModel(),
                result.getVIN(),                  
                result.getStateNumber(), 
                result.getMileage(),
                result.getFuel(),
                result.getFuelTankCapacity(),
                result.getFuelConsumption(),
                result.getThings()
            );

            newCar->setCarStereo(result.getCarStereo());
            newCar->setCurrentWorkshop(result.getCurrentWorkshop());

            cars.push_back(move(newCar));
            cout << "Новый автомобиль создан и сохранен!" << endl;
        }

    }
    catch (const exception& e) {
        cout << "Ошибка при выполнении оператора: " << e.what() << endl;
    }
}

void performActionOnAll() {
    cout << "\n=== ВЫПОЛНЕНИЕ ДЕЙСТВИЙ ДЛЯ ВСЕХ ОБЪЕКТОВ ===" << endl;

    cout << "Выберите тип объектов:" << endl;
    cout << "1. Все автомобили" << endl;
    cout << "2. Все автомастерские" << endl;
    cout << "3. Все магнитолы" << endl;
    cout << "Выбор: ";

    int typeChoice;
    cin >> typeChoice;

    switch (typeChoice) {
    case 1:
        for (auto& car : cars) {
            cout << "\n--- Действия для " << car->getBrand() << " " << car->getModel() << " ---" << endl;
            performCarActions(*car);
        }
        break;

    case 2:
        for (auto& workshop : workshops) {
            cout << "\n--- Действия для мастерской: " << workshop->getAddress() << " ---" << endl;
            performWorkshopActions(*workshop);
        }
        break;

    case 3:
        for (auto& stereo : stereos) {
            cout << "\n--- Магнитола: " << stereo.modelName << " ---" << endl;
            stereo.displayInfo();
        }
        break;

    default:
        cout << "Неверный выбор!" << endl;
    }
}

void performCarActions(Car& car) {
    int actionChoice;
    do {
        cout << "\nВыберите действие для автомобиля " << car.getBrand() << " " << car.getModel() << ":" << endl;
        cout << "1. Показать полную информацию" << endl;
        cout << "2. Заправить" << endl;
        cout << "3. Проехать расстояние" << endl;
        cout << "4. Скрутить пробег" << endl;
        cout << "5. Установить магнитолу" << endl;
        cout << "6. Сменить мастерскую" << endl;
        cout << "7. Добавить вещь в багажник" << endl;
        cout << "0. Завершить действия с этим автомобилем" << endl;
        cout << "Выбор: ";
        cin >> actionChoice;

        try {
            switch (actionChoice) {
            case 1: car.displayInfo(); break;
            case 2: {
                int liters;
                cout << "Количество литров для заправки: ";
                cin >> liters;
                car.refuel(liters);
                break;
            }
            case 3: {
                int distance;
                cout << "Расстояние для поездки (км): ";
                cin >> distance;
                car.addKilometers(distance);
                break;
            }
            case 4: {
                int km;
                cout << "Скрутить пробег на (км): ";
                cin >> km;
                car.updateMileage(km);
                break;
            }
            case 5: {
                CarStereo* stereo = selectStereo("Выберите магнитолу:");
                if (stereo) {
                    car.setCarStereo(stereo);
                }
                break;
            }
            case 6: {
                AutoWorkshop* workshop = selectWorkshop("Выберите новую мастерскую:");
                if (workshop) {
                    // Находим текущую мастерскую
                    AutoWorkshop* currentWorkshop = nullptr;
                    for (auto& w : workshops) {
                        if (w->getAddress() == car.getCurrentWorkshop()) {
                            currentWorkshop = w.get();
                            break;
                        }
                    }

                    if (currentWorkshop) {
                        currentWorkshop->detachCar(&car);
                    }

                    workshop->attachCar(&car);
                    car.setCurrentWorkshop(workshop->getAddress());
                }
                break;
            }
            case 7: {
                string item;
                cout << "Введите вещь для добавления: ";
                cin >> item;
                auto things = car.getThings();
                things.push_back(item);
                car.setThings(things);
                cout << "Вещь добавлена!" << endl;
                break;
            }
            case 0: break;
            default: cout << "Неверный выбор!" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

    } while (actionChoice != 0);
}

void performWorkshopActions(AutoWorkshop& workshop) {
    int actionChoice;
    do {
        cout << "\nВыберите действие для мастерской " << workshop.getAddress() << ":" << endl;
        cout << "1. Показать полную информацию" << endl;
        cout << "2. Добавить магнитолу" << endl;
        cout << "3. Установить магнитолу на автомобиль" << endl;
        cout << "4. Прикрепить автомобиль" << endl;
        cout << "5. Открепить автомобиль" << endl;
        cout << "0. Завершить действия с этой мастерской" << endl;
        cout << "Выбор: ";
        cin >> actionChoice;

        try {
            switch (actionChoice) {
            case 1: workshop.displayInfo(); break;
            case 2: {
                CarStereo* stereo = selectStereo("Выберите магнитолу:");
                if (stereo) {
                    workshop.addStereo(*stereo);
                }
                break;
            }
            case 3: {
                Car* car = selectCar("Выберите автомобиль:");
                if (!car) break;

                cout << "Выберите магнитолу из доступных:" << endl;
                auto availableStereos = workshop.getAvailableStereos();
                for (size_t i = 0; i < availableStereos.size(); i++) {
                    cout << i + 1 << ". " << availableStereos[i].modelName << endl;
                }

                if (!availableStereos.empty()) {
                    cout << "Номер магнитолы: ";
                    int stereoChoice;
                    cin >> stereoChoice;

                    if (stereoChoice > 0 && stereoChoice <= availableStereos.size()) {
                        workshop.installStereoToCar(car, availableStereos[stereoChoice - 1].modelName);
                        car->setCarStereo(&availableStereos[stereoChoice - 1]);
                    }
                }
                break;
            }
            case 4: {
                Car* car = selectCar("Выберите автомобиль для прикрепления:");
                if (car) {
                    workshop.attachCar(car);
                    car->setCurrentWorkshop(workshop.getAddress());
                }
                break;
            }
            case 5: {
                auto attachedCars = workshop.getAttachedCars();
                if (attachedCars.empty()) {
                    cout << "Нет прикрепленных автомобилей!" << endl;
                    break;
                }

                cout << "Прикрепленные автомобили:" << endl;
                for (size_t i = 0; i < attachedCars.size(); i++) {
                    cout << i + 1 << ". " << attachedCars[i]->getBrand()
                        << " " << attachedCars[i]->getModel() << endl;
                }

                cout << "Номер автомобиля для открепления: ";
                int carChoice;
                cin >> carChoice;

                if (carChoice > 0 && carChoice <= attachedCars.size()) {
                    workshop.detachCar(attachedCars[carChoice - 1]);
                    attachedCars[carChoice - 1]->setCurrentWorkshop("Не прикреплен");
                }
                break;
            }
            case 0: break;
            default: cout << "Неверный выбор!" << endl;
            }
        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << endl;
        }

    } while (actionChoice != 0);
}

void saveToFile() {
    cout << "\n=== СОХРАНЕНИЕ В ФАЙЛ ===" << endl;
    cout << "Сохранение данных в файл..." << endl;

    // Здесь можно реализовать сохранение в файл
    // Это упрощенная версия - в реальном проекте нужно полноценное сохранение

    cout << "Функция сохранения в файл будет реализована в следующей версии." << endl;
    cout << "В настоящее время все данные хранятся только в оперативной памяти." << endl;
}

void loadFromFile() {
    cout << "\n=== ЗАГРУЗКА ИЗ ФАЙЛА ===" << endl;
    cout << "Загрузка данных из файла..." << endl;

    // Здесь можно реализовать загрузку из файла
    // Это упрощенная версия

    cout << "Функция загрузки из файла будет реализована в следующей версии." << endl;
}

void clearAllData() {
    cout << "\n=== ОЧИСТКА ВСЕХ ДАННЫХ ===" << endl;
    cout << "Вы уверены, что хотите удалить все данные? (1 - да, 0 - нет): ";

    int confirm;
    cin >> confirm;

    if (confirm == 1) {
        cars.clear();
        workshops.clear();
        stereos.clear();

        // Создаем минимальный набор для продолжения работы
        stereos.push_back(CarStereo("Базовая магнитола", "Тестовая модель", 10000));
        workshops.push_back(make_unique<AutoWorkshop>("Центральная мастерская"));

        cout << "Все данные очищены!" << endl;
        cout << "Созданы тестовые объекты для продолжения работы." << endl;
    }
}

// Вспомогательные функции для выбора объектов
Car* selectCar(const string& prompt) {
    if (cars.empty()) {
        cout << "Нет доступных автомобилей!" << endl;
        return nullptr;
    }

    cout << prompt << endl;
    for (size_t i = 0; i < cars.size(); i++) {
        cout << i + 1 << ". " << cars[i]->getBrand() << " "
            << cars[i]->getModel() << " (" << cars[i]->getStateNumber() << ")" << endl;
    }

    int choice;
    cout << "Выбор (0 для отмены): ";
    cin >> choice;

    if (choice == 0 || choice > cars.size()) {
        return nullptr;
    }

    return cars[choice - 1].get();
}

AutoWorkshop* selectWorkshop(const string& prompt) {
    if (workshops.empty()) {
        cout << "Нет доступных автомастерских!" << endl;
        return nullptr;
    }

    cout << prompt << endl;
    for (size_t i = 0; i < workshops.size(); i++) {
        cout << i + 1 << ". " << workshops[i]->getAddress() << endl;
    }

    int choice;
    cout << "Выбор (0 для отмены): ";
    cin >> choice;

    if (choice == 0 || choice > workshops.size()) {
        return nullptr;
    }

    return workshops[choice - 1].get();
}

CarStereo* selectStereo(const string& prompt) {
    if (stereos.empty()) {
        cout << "Нет доступных магнитол!" << endl;
        return nullptr;
    }

    cout << prompt << endl;
    for (size_t i = 0; i < stereos.size(); i++) {
        cout << i + 1 << ". " << stereos[i].modelName
            << " (" << stereos[i].price << " руб.)" << endl;
    }

    int choice;
    cout << "Выбор (0 для отмены): ";
    cin >> choice;

    if (choice == 0 || choice > stereos.size()) {
        return nullptr;
    }

    return &stereos[choice - 1];
}

void pressEnterToContinue() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore();
    cin.get();
}