ю// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <string>
using namespace std;
int main()
{
    setlocale(LC_ALL, "Russian");
    //Часть 1
    cout << "Введите кол-во членов последовательности" << endl;
    short n;
    cin >> n;
    int sum_even = 0;
    short c = 0;
    short nu = 0;
    short mnu = 0;
    int m;
    int cc = 0;
    for (short i = 1; i <= n; i++)
    {
        int a;
        cin >> a;
        if (a % 2 == 0)
        {
            if (cс != 1)
            {
                if (a % 2 == 0)
                {
                    m = a;
                    cс = 1;
                    mnu = nu + 1;
                }
            }
            sum_even += a;
            nu += 1;

            if (a > m)
            {
                m = a;
                mnu = nu;
            }
        }
        else
        {
            c += 1;
            nu += 1;
        }
    } if (c != n)
    {
        cout << "Сумма четных числе последовательности: " << sum_even << endl << "Максимальное четное число последовательности: " << m << endl << "Его номер: " << mnu << endl;
    }
    else
    {
        cout << "Не найдено членов последовательности, удовлетворяющих условию" << endl;
    }
    //Часть 2
    short x;
    cin >> x;
    x = abs(x);
    short mi = 99;
    while (x > 0)
    {
        short c = x % 10;
        x = x / 10;
        if (c != 0 && c != 7)
        {
            if (c < mi)
            {
                mi = c;
            }
        }
    }
    if (mi != 99)
    {
        cout << mi;
    }
    else
    {
        cout << "Число состоит из 7 и 0";
    }

}
