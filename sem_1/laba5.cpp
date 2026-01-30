// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;
int func(int& a, int& b)
{
    cout << "Используется функция для двух чисел" << endl;
    return (a + 2 * b + 3);
}
int func(int& a, int& b, int& c)
{
    cout << "Используется функция для нахождения максимальной попарной суммы" << endl;
    int ac = a + c;
    int bc = b + c;
    int ab = a + c;
    int res = ac;
    if (bc > res)
    {
        res = bc;
    }

    if (ab > res)
    {
        res = ab;
    }
    return res;
}

void gipp(int& k1, int& k2)
{
    double gippo = sqrt(pow(k1, 2) + pow(k2, 2));
    cout << gippo << endl;

    short int_bit = sizeof(int);
    int min_int = std::numeric_limits<int>::min();
    int max_int = std::numeric_limits<int>::max();
    std::cout << "int, занимает " << int_bit << " бита,мин. значение = " << min_int << " ,макс. значение = " << max_int << std::endl;
    short sh_bit = sizeof(short);
    short min_short = std::numeric_limits<short>::min();
    short max_short = std::numeric_limits<short>::max();
    std::cout << "short, занимает " << sh_bit << " бита,мин. значение = " << min_short << " ,макс. значение = " << max_short << std::endl;
    short db_bit = sizeof(double);
    std::cout << "double, занимает " << db_bit << " бита,мин. значение = " << std::numeric_limits<double>::lowest() << " ,макс. значение = " << std::numeric_limits<double>::max() << std::endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    //часть 1
    cout << "Введите три числа, вместо ненужного укажите ноль" << endl;
    int a, b, c;
    cin >> a >> b >> c;
    cout << "Выберите номер функции для использования" << endl;
    short func_num;
    cin >> func_num;
    if (func_num == 1)
    {
        if ((a != 0 && b != 0) && c == 0)
        {
            cout << func(a, b) << endl;
        }
        else if ((b != 0 && c != 0) && a == 0)
        {
            cout << func(b, c) << endl;
        }
        else if ((a != 0 && c != 0) && b == 0)
        {
            cout << func(a, c) << endl;
        }
        else if ((a != 0 && b != 0) && c != 0)
        {
            cout << func(a, b, c) << endl;
        }
        else 
        {
            cout << "Недостаточно чисел";
        }
    }

    if (func_num == 2)
    {

        cout << "Введите катеты" << endl;
        int k1, k2;
        cin >> k1 >> k2;
        gipp(k1, k2);
    }

}
