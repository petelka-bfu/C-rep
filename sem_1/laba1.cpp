// laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cmath>
#include <climits>

int main()
{
	setlocale(LC_ALL, "Russian");
	unsigned int kat1;
	int kat2;
	std::cin >> kat1;
	std::cin >> kat2;
	double gippo = sqrt(pow(kat1, 2) + pow(kat2, 2));
	double perri = gippo + kat1 + kat2;
	std::cout << "Гипотенуза = " << gippo << std::endl;
	std::cout << "Периметр = " << perri << std::endl;

	short unint_bit = sizeof(unsigned int);
	unsigned int min_unint = std::numeric_limits<unsigned int>::min();
	unsigned int max_unint = std::numeric_limits<unsigned int>::max();
	std::cout << "unsigned int, занимает " << unint_bit << " бита,мин. заначение = " << min_unint << " ,макс. значение = " << max_unint << std::endl;
	short int_bit = sizeof(int);
	int min_int = std::numeric_limits<int>::min();
	int max_int = std::numeric_limits<int>::max();
	std::cout << "int, занимает " << int_bit << " бита,мин. значение = " << min_int << " ,макс. значение = " << max_int << std::endl;
	short sh_bit = sizeof(short);
	short min_short = std::numeric_limits<short>::min();
	short max_short = std::numeric_limits<short>::max();
	std::cout << "short, занимает " << sh_bit << " бита,мин. значение = " << min_short << " ,макс. значение = " << max_short << std::endl;
	short db_bit = sizeof(double);
	std::cout << "double, занимает " << db_bit << " бита,мин. значение = " << std::numeric_limits<double>::min() << " ,макс. значение = " << std::numeric_limits<double>::max() << std::endl;

}
