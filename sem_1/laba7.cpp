
#include <iostream>﻿
#include <vector>
#include <random>
#include <ctime>
#include <array>
using namespace std;
//Функции для пункта 1
void ArrayCheck(const vector<int>& array) // вывод массива
{
    cout << "[";
    for (size_t i = 0; i < array.size(); ++i) {
        cout << array[i];
        if (i < array.size() - 1) cout << " ";
    }
    cout << "]" << endl;
}

void End(vector<int>& arr, int value) //добавление элемента в конец
{
    arr.push_back(value);
}

void Clear(vector<int>& arr) //очистка
{
    arr.clear();
}

vector<size_t> FindElement(const vector<int>& arr, int value) // поиск элемента
{
    vector<size_t> index;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == value) {
            index.push_back(i);
        }
    }
    return index;
}

void Begin(vector<int>& array, int value) // добавление элемента в начало
{
    array.insert(array.begin(), value);
}

void IndexOut(const vector<size_t>& indices) { // вывод идексов
    cout << "[";
    for (size_t i = 0; i < indices.size(); ++i) {
        cout << indices[i];
        if (i < indices.size() - 1) cout << ",";
    }
    cout << "]" << endl;
}

void Zadanie_var(std::vector<int>& array) { // задание варианта
    for (size_t i = 0; i < array.size(); ++i) {
        if (array[i] % 2 == 0) {
            array[i] += 2;
        }
        else {
            array[i] = -array[i];
        }
    }
}

void Punct1() // общая функция(выводит меню, принимает команды)
{
    vector <int>array;
    short number;
    while (true) {
        cout << "1. Просмотр массива." << endl;
        cout << "2. Добавить элемент в начало." << endl;
        cout << "3. Добавить элемент в конец." << endl;
        cout << "4. Очистка всего массива." << endl;
        cout << "5. Поиск элемента в массиве." << endl;
        cout << "6. Добавить к четным элементам 2, а нечетным поменять знак." << endl;
        cout << "0.Выйти" << endl;
        cout << "Введите номер пункта" << endl;
        cin >> number;
        if (number == 0) {
            break;
        }
        switch (number)
        {
        case 0:
            cout << "Выход" << endl;
            break;
        case 1:
            cout << "Выбран просмотр массива" << endl;
            ArrayCheck(array);
            break;
        case 2:
            cout << "Выбрано добавить элемент в начало" << endl;
            cout << "Введите элемент котрый нужно добавить в начало" << endl;
            int n;
            cin >> n;
            Begin(array, n);
            break;
        case 3:
            cout << "Выбрано добавить элемент в конец" << endl;
            cout << "Введите элемент котрый нужно добавить в конец" << endl;
            int no;
            cin >> no;
            End(array, no);
            break;
        case 4:
            cout << "Выбрана очистка всего массива" << endl;
            Clear(array);
            break;
        case 5:
        {
            cout << "Выбран поиск элемента в массиве" << endl;
            cout << "Введите элемент котрый нужно найти" << endl;
            int na;
            cin >> na;
            vector<size_t> index = FindElement(array, na);
            cout << "Индексы элемента: ";
            IndexOut(index);
            break;
        }
        case 6:
            cout << "Выбрано добавить к четным элементам 2, а нечетным поменять знак" << endl;
            Zadanie_var(array);
            break;
        default:
            cout << "Такого пункта в меню нет" << "\n";
            break;

        }
    }
}

//Функции для пункта 2
int randomNumber() {
    static mt19937 gen(time(0));
    static uniform_int_distribution<int> dis(-10, 10);
    return dis(gen);
}
void Zapol(array<int, 10>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        arr[i] = randomNumber();
    }
}
void ArrayCheck(const array<int, 10>& arr) {
    cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i];
        if (i != arr.size() - 1) cout << " ";
    }
    cout << "]" << endl;
}
void sort_link(std::array<int, 10>& massive)//
{
    bool sw;
    int size = massive.size();
    for (int i = 0; i < size; ++i)
    {
        sw = false;
        for (int j = 0; j < size - 1 - i; ++j)
        {
            if (massive[j] > massive[j + 1])
            {
                std::swap(massive[j], massive[j + 1]);
                sw = true;
            }
        }
        if (!sw) break;
    }
    cout << "После сортировки по значению(в функции) по возрастанию" << endl;
    ArrayCheck(massive);
    for (int i = 0; i < size; ++i)
    {
        sw = false;
        for (int j = 0; j < size - 1 - i; ++j)
        {
            if (massive[j] < massive[j + 1])
            {
                std::swap(massive[j], massive[j + 1]);
                sw = true;
            }
        }
        if (!sw) break;
    }
    cout << "После сортировки по значению(в функции) по убыванию" << endl;
    ArrayCheck(massive);
}
void sort_pointer(array<int, 10>* massive)//
{
    if (massive == nullptr) return;

    bool sw;
    for (int i = 0; i < 10; ++i)
    {
        sw = false;
        for (int j = 0; j < 9 - i; ++j)
        {
            if ((*massive)[j] > (*massive)[j + 1])
            {
                swap((*massive)[j], (*massive)[j + 1]);
                sw = true;
            }
        }
        if (!sw) break;
    }
    cout << "После сортировки по значению(в функции) по возрастанию" << endl;
    ArrayCheck(*massive);
    for (int i = 0; i < 10; ++i)
    {
        sw = false;
        for (int j = 0; j < 9 - i; ++j)
        {
            if ((*massive)[j] < (*massive)[j + 1])
            {
                swap((*massive)[j], (*massive)[j + 1]);
                sw = true;
            }
        }
        if (!sw) break;
    }
    cout << "После сортировки по значению(в функции) по убыванию" << endl;
    ArrayCheck(*massive);
}
void sort_copy(array<int, 10> massive)//
{
    bool sw;
    for (int i = 0; i < 10; ++i)
    {
        sw = false;
        for (int j = 0; j < 9 - i; ++j)
        {
            if (massive[j] > massive[j + 1])
            {
                std::swap(massive[j], massive[j + 1]);
                sw = true;
            }
        }
        if (!sw)
        {
            break;
        }
    }
    cout << "После сортировки по значению(в функции) по возрастанию" << endl;
    ArrayCheck(massive);

    for (int i = 0; i < 10; ++i)
    {
        sw = false;
        for (int j = 0; j < 9 - i; ++j)
        {
            if (massive[j] < massive[j + 1])
            {
                std::swap(massive[j], massive[j + 1]);
                sw = true;
            }
        }
        if (!sw)
        {
            break;
        }
    }
    cout << "После сортировки по значению(в функции) по убыванию" << endl;
    ArrayCheck(massive);
}


void elem_search(const std::vector<int>& massive, int& num)
{
    std::cout << "[";
    int length = massive.size();
    short k = 0;
    for (int i = 0; i < length; ++i)
    {
        if (massive[i] == num)
        {
            if (k == 0)
            {
                std::cout << i;
            }
            else
            {
                std::cout << ',' << i;
            }
            k += 1;
        }
    }
    std::cout << "]" << endl;
}
void Punct2()
{
    array<int, 10> arrayy;
    Zapol(arrayy);
    cout << "Исходный массив" << endl;
    ArrayCheck(arrayy);

    // по занчению
    cout << "Передача массива в функцию по значению создает полную копию массива." << endl;
    cout << "Изменения внутри функции не влияют на исходный массив." << endl;
    cout << "Требует дополнительной памяти для копии" << endl;
    cout << "Медленнее из-за копирования" << endl;

    array<int, 10> copy_array = arrayy;
    sort_copy(copy_array);
    cout << "После сортировки по значению(снаружи функции):" << endl;
    ArrayCheck(copy_array);
    cout << endl;

    // по ссылке
    cout << "Передача массива в функцию по ссылке работает напрямую с исходным массивом." << endl;
    cout << "Изменения внутри функции влияют на оригинальный массив." << endl;
    cout << "Не требует дополнительной памяти" << endl;
    cout << "быстрее, нет копирования" << endl;

    sort_link(arrayy);
    cout << "После сортировки по ссылке(снаружи фукнции):" << endl;
    ArrayCheck(arrayy);
    cout << endl;

    // по указателю
    cout << "Передача массива в функцию по указателю работает с исходным массивом." << endl;
    cout << "Изменения внутри функции влияют на оригинальный массив." << endl;
    cout << "требует памяти только для хранения указателя " << endl;
    cout << "быстрее, нет копирования" << endl;
    cout << "Нужно проверять указатель на nullptr" << endl;

    sort_pointer(&arrayy);
    cout << "После сортировки по указателю(снаружи функции):" << endl;
    ArrayCheck(arrayy);

}
int main()
{
    setlocale(LC_ALL, "Russian");
    Punct1();
    Punct2();

}
