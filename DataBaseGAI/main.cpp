#include<iostream>
#include<map>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------\n"

#define DATA_BASE_GAI

void main()
{
	setlocale(LC_ALL, "");

#ifdef DATA_BASE_GAI

	std::multimap<int, std::string>offence =
	{
		std::pair<int,std::string>(521,"Превышение установленной скорости движения"),
		std::pair<int,std::string>(521,"Парковка в неположенном месте"),
		std::pair<int,std::string>(229,"Ехал на запрещающий сигнал светофора"),
		std::pair<int,std::string>(229,"Нарушение правил перевозки людей"),
		std::pair<int,std::string>(229,"Парковка в неположенном месте"),
		std::pair<int,std::string>(325,"Обгон в запрещенном месте"),
		std::pair<int,std::string>(325,"Нарушение правил пользования телефоном водителем ТС"),
		std::pair<int,std::string>(405,"Нарушение правил применения ременей безопасности"),
		std::pair<int,std::string>(405,"Превышение установленной скорости движения"),
		std::pair<int,std::string>(405,"Пересечение стоп-линии на запрещающий сигнал светофора"),
		std::pair<int,std::string>(377,"Превышение установленной скорости движения"),
		std::pair<int,std::string>(377,"Ехал на запрещающий сигнал светофора"),
		std::pair<int,std::string>(147,"Превышение установленной скорости движения"),
		std::pair<int,std::string>(147,"Несоблюдение требований об обязательном страховании владельцев ТС"),
		std::pair<int,std::string>(228,"Парковка в неположенном месте"),
		std::pair<int,std::string>(228,"Передал управление автомобилем человеку без прав"),
		std::pair<int,std::string>(756,"Превышение установленной скорости движения"),
	};

	for (std::map<int, std::string>::iterator it = offence.begin(); it != offence.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}

	int n;
	cout << "Введите номер автомобиля: "; cin >> n;
	for (std::map<int, std::string>::iterator it = offence.begin(); it != offence.end(); ++it)
		cout << n << endl;
#endif // DATA_BASE_GAI

}