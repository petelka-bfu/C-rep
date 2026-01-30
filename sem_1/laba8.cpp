#include <iostream> 
#include <string>

using namespace std;
struct season
{
	string seas;
	string m1;
	string m2;
	string m3;
	string nextseas;
	void Output() 
	{
		cout << "Какой элемент вы хотите вывести?" << endl;
		cout << "1 - время года, 2 - первый месяц, 3 - второй месяц , 4 - третий месяц, 5 - следующий сезон" << endl;
		short a;
		cin >> a;
		switch (a)
		{ 
		case 1:
		
			cout << seas << endl;
			break;
		case 2:
		
			cout << m1 << endl;
			break;
		case 3:
		
			cout << m2 << endl;
			break;
		case 4:
		
			cout << m3 << endl;
			break;
		case 5:
		
			cout << nextseas << endl;
			break;
		
		}
	}
	void printYear()
	{
		
		cout << seas << "[" << m1 << ", " << m2 << ", " << m3 << "] ";
	}
	
};

void Year(season a, season b, season c, season d)
{
	a.printYear();
	b.printYear();
	c.printYear();
	d.printYear();
	cout << endl;
};
void Swapp(season& a, season& b, short aa, short bb)
{
	string* monthA = nullptr;
	switch (aa)
	{
	case 1: monthA = &a.m1; break;
	case 2: monthA = &a.m2; break;
	case 3: monthA = &a.m3; break;
	default:
		cout << "Неверный номер месяца" << endl;
		break;
	}

	string* monthB = nullptr;
	switch (bb)
	{
	case 1: monthB = &b.m1; break;
	case 2: monthB = &b.m2; break;
	case 3: monthB = &b.m3; break;
	default:
		cout << "Неверный номер месяца" << endl;
		break;
	}
	swap(*monthA, *monthB);
}
void Menu(season& Winter, season& Spring, season& Summer, season& Autumn)
{
	while (true)
	{
		cout << "1.Смена месяцев местами" << endl;
		cout << "2.Просмотр элемента" << endl;
		cout << "3.Просмотр года" << endl;
		short a;
		cin >> a;
		switch (a)
		{
		case 1: {
			cout << "Выбран обмен месяцами" << endl;
			cout << "Выберите первый сезон:" << endl;
			cout << "1. Зима, 2. Весна, 3. Лето, 4. Осень: ";
			int season1;
			cin >> season1;

			cout << "Выберите месяц в этом сезоне: ";
			int month1;
			cin >> month1;

			cout << "Выберите второй сезон:" << endl;
			cout << "1. Зима, 2. Весна, 3. Лето, 4. Осень: ";
			int season2;
			cin >> season2;

			cout << "Выберите месяц во втором сезоне: ";
			int month2;
			cin >> month2;

			// Определяем, какие сезоны выбраны
			season* s1 = nullptr;
			season* s2 = nullptr;

			switch (season1) {
			case 1: s1 = &Winter; break;
			case 2: s1 = &Spring; break;
			case 3: s1 = &Summer; break;
			case 4: s1 = &Autumn; break;
			default: cout << "Нет такого сезона" << endl; break;
			}

			switch (season2) {
			case 1: s2 = &Winter; break;
			case 2: s2 = &Spring; break;
			case 3: s2 = &Summer; break;
			case 4: s2 = &Autumn; break;
			default: cout << "Нет такого сезона" << endl; break;
			}

			if (s1 && s2) {
				Swapp(*s1, *s2, month1, month2);
			}
			break;
		}

		case 2: {
			cout << "Выбран просмотр элемента" << endl;
			cout << "Выберите сезон:" << endl;
			cout << "1. Зима, 2. Весна, 3. Лето, 4. Осень: ";
			int s;
			cin >> s;

			switch (s) {
			case 1: Winter.Output(); break;
			case 2: Spring.Output(); break;
			case 3: Summer.Output(); break;
			case 4: Autumn.Output(); break;
			default: cout << "Нет такого сезона" << endl; break;
			}
			break;
		}

		case 3: {
			cout << "Выбран просмотр года " << endl;
			Year(Winter, Spring, Summer, Autumn);
			break;
		}

		default:
			cout << "Нет такой команды" << endl;
			break;
		}
	}
}
int main() 
{
	setlocale(LC_ALL, "Russian");
	season Winter = { "Зима","Декабрь","Январь","Февраль","Весна" };
	season Spring = { "Весна","Март", "Апрель", "Май", "Лето" };
	season Summer = { "Лето","Июнь", "Июль", "Август", "Осень" };
	season Autumn = { "Осень","Сентябрь", "Октябрь", "Ноябрь", "Зима" };
	Menu(Winter, Spring, Summer, Autumn);
}
