// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <bitset>
int main()
{
	setlocale(LC_ALL, "Russian");
	//Часть 1
	//Принимаю переменную а
	short a;
	std::cout << "Введите А: ";
	std::cin >> a;
	//принимаю переменную i
	short i;
	std::cout << "Введите номер бита: ";
	std::cin >> i;

	if (0 <= i && i <= 7)
	{
		short e = ((a >> i) & 1);
		std::bitset<8> bit(a);

		std::cout << bit << std::endl;

		if (e == 1){
			int b;
			int c;
			std::cout << "Введите два целочисленных числа" << std::endl;
			std::cin >> b;
			std::cin >> c;
			if (b > c) {
				std::bitset<8> bb(b);
				std::cout << bb << std::endl;
			}
			else {
				std::bitset<8> cc(c);
				std::cout << cc << std::endl;
			}
	}
			
		else
		{
			
			bit = ~bit;
			std::cout << bit << std::endl;
		}
	}
	else
	{
		std::cout << "Неверный номер бита" << std::endl;
	}
	short n;
	std::cout << "ВВедите номер месяца" << std::endl;
	std::cin >> n;
	switch (n)
	{
	case 1:
		std::cout << "Январь";
		break;
	case 2:
		std::cout << "Февраль";
		break;
	case 3:
		std::cout << "Март";
		break;
	case 4:
		std::cout << "Апрель";
		break;
	case 5:
		std::cout << "Май";
		break;
	case 6:
		std::cout << "Июнь";
		break;
	case 7:
		std::cout << "Июль";
		break;
	case 8:
		std::cout << "Август";
		break;
	case 9:
		std::cout << "Сентябрь";
		break;
	case 10:
		std::cout << "Октябрь";
		break;
	case 11:
		std::cout << "Ноябрь";
		break;
	case 12:
		std::cout << "Декабрь";
		break;
	default:
		std::cout << "Месяца под таким номером не существует";
	}
}



