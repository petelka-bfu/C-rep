// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
using namespace std;
int main() 
{
    setlocale(LC_ALL, "Russian");
    //часть 1
    const short aa = 4;
    int arr[aa];
    int mb = 10;
    int mc = 10;
    cout << "Введите элементы массива:" << endl;
    for (int i = 0; i < aa; i++) //принимаю занчения в массив
    {
        cin >> arr[i];
    }
    int b = arr[0];
    int c = arr[3];
    while (c  >= 10) //нахожу минимальную цифру в последннем числе массива
    {
        if (mc > c % 10)
        {
            mc = c % 10;
        }
        c = c / 10;
    }
    while (b >= 10) //тоже самое с первым числом массива
    {
        if (mb > b % 10)
        {
            mb = b % 10;
        }
        b = b / 10;
    }
    if (mb == mc) //если совпадают, то сортировка по возрастанию
    {
        for (int i = 0; i < aa - 1; ++i)
        {
            for (int j = i + 1; j < aa; ++j)
            {
                if (arr[i] > arr[j])
                {
                    swap(arr[i], arr[j]);
                }
            }
        }
    }
    for (int i = 0; i < aa; i++) //вывод
    {
        cout << arr[i] << endl;
    }
    //часть 2
    int zer;
    int cc = 0;
    int ns;
    int i, j, n, m, a[3][4];
    n = 3;
    m = 4;
    cout << "Введите матрицу" << endl;
    for (i = 0; i < n; i++) //принимаю занчения в матрицу
    {
        for (j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    for (i = 0; i < n; i++)
    {
        int sum = 0;
        for (j = 0; j < m; j++) //проверка(сумма какой строчки матрицы ближе всего к 0) 
        {
            sum += a[i][j];
        }
        if (cc != 1)
        {
            zer = abs(sum);
            cc = 1;
            ns = i;
        }
        if (abs(sum) < zer)
        {
            ns = i;
            zer = abs(sum);
        }
    }


    for (j = 0; j < m; j++) //приравнивание этой строчки к нулю
    {
        a[ns][j] = 0;
    }



    for (i = 0; i < n; i++) //вывод
    {
        for (j = 0; j < m; j++)
        {
            cout << a[i][j] << "\t";
        }
        cout << endl;
    }

}
