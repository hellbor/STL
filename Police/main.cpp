﻿#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
#include<Windows.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------------------------\n"

#define Enter		13
#define Escape		27
#define UP_ARROW	72
#define DOWN_ARROW	80

//const char* MENU_ITEMS[] =
//{
//	"1. Загрузить базы из файла",
//	"2. Сохранить базу в файл",
//	"3. Вывести базу на экран",
//	"4. Вывести информацию по номеру",
//	"5. Добавить нарушение",
//};
//const int MENU_SIZE = sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]);

const std::map<int, std::string>MENU_ITEMS =
{
	{1, "Загрузить базы из файла"},
	{2, "Сохранить базу в файл"},
	{3, "Вывести базу на экран"},
	{4, "Добавить нарушение"},
	{5, "Вывести информацию по номеру"},
};

const std::map<int, std::string> VIOLATION =
{
	{0,"N/A"},
	{1,"Ремень безопасности"},
	{2,"Парковка в неположенном месте"},
	{3,"Пересечение сплошной линии"},
	{4,"Превышение скорости"},
	{5,"Отсутствие водительского удостоверения"},
	{6,"Отсутствие права управления автомобиля"},
	{7,"Отсутствие страховки"},
	{8,"Проезд на красный"},
	{9,"Выезд на встречную полосу"},
	{10,"Дрифт на перекрестке"},
	{11,"Езда в нетрезвом состоянии"},
	{12,"Оскорбление офицера"},
	{13,"Внесение изменений в конструкцию автомобиля"},
	{14,"Перевозка негабаритного груза"},
	{15,"Превышение максимальной нагрузки на ось"},
	{16,"Перевозка ребенка без кресла"},
};

class Crime
{
	int id;
	//int violation;
	std::string place;
	tm time;
public:
	/*const std::string& get_license_plate()const
	{
		return license_plate;
	}*/
	const int get_violation_id()const
	{
		return id;
	}
	const std::string& get_violations()const
	{
		return VIOLATION.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
	}

	/*void get_license_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		//1. Создаем временую строку для того, чтобы пропарсить полученную строку
		char* time_buffer = new char[time.size() + 1] {};
		//2. Копируем полученную строку в буфер:
		strcpy(time_buffer, time.c_str());
		//Функция strcpy(dst, src); копирует содержимое строки-источника в строку получателя

		//3) Создаем массив для хранения элементов времени:
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		//функция std::atoi() 'ASCII-string to int' преобразует строку в целое число
		delete[] time_buffer;

		//4) Сохраняем элементы времени в структуру 'tm':

		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;

		//this->time=time;
	}
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}

	//					Constructors
	Crime(int violation_id, const std::string& place, const std::string& time)
	{
		this->time = {};
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);
#ifdef DEBUG
		cout << "Constuctor:\t" << this << endl;
#endif // DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif // DEBUG
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_violations();
}
std::ofstream& operator<<(std::ofstream& os, const Crime& obj)
{
	os << obj.get_violation_id() << " " << obj.get_timestamp() << " " << obj.get_place();
	return os;
}
std::istream& operator>>(std::istream& is, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	is >> id >> timestamp;
	std::getline(is, place, ',');
	is.ignore();
	obj.set_violation_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}

int menu();
void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename);
std::map<std::string, std::list<Crime>>load(const std::string& filename);
void add_crime(std::map<std::string, std::list<Crime>>& base);
void print_by_number(const std::map<std::string, std::list<Crime>>& base);

//#define SAVE_CHECK
//#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef SAVE_CHECK
	/*Crime crime(1, "ул. Ленина", "18:10 1.09.2024");
cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb", {Crime(1, "ул. Ленина", "18:10 1.09.2024"),
		Crime(2,"пл. Свободы", "12:25 20.08.2024")}},
		{"a000bb", {Crime(6, "ул. Космонавтов", "17:50 1.08.2024"),
		Crime(8,"ул. Космонавтов", "17:45 1.08.2024")}},
		{"a001aa", {Crime(10, "ул. Пролетарская", "21:50 1.08.2024"),
		Crime(9,"ул. Пролетарская", "21:50 1.08.2024"),
		Crime(11, "ул. Пролетарская", "21:50 1.08.2024"),
		Crime(12,"ул. Пролетарская", "22:05 1.08.2024")}},
	};
	print(base);
	save(base, "base.txt");
#endif // SAVE_CHECK

#ifdef LOAD_CHECK
	std::map<std::string, std::list<Crime>>base = load("base.txt");
	print(base);
#endif // DEBUGload

	std::map<std::string, std::list<Crime>>base = load("base.txt");
	do
	{
		switch (menu())
		{
		case 0: return;
		case 1: base = load("base,txt"); break;
		case 2: save(base, "base,txt");	 break;
		case 3: print(base);			 break;
		case 4: add_crime(base);		 break;
		case 5: print_by_number(base);   break;
		case 6: exit(0);
		}
	} while (true);
}

int menu()
{
	int selected_item = 1;
	char key;
	do
	{
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 1; i <= MENU_ITEMS.size(); i++)
		{
			cout << (i == selected_item ? "[" : " ");
			cout << i << ". ";
			cout.width(32);
			cout << std::left;
			if (i == selected_item)SetConsoleTextAttribute(hConsole, 0x70);
			cout << MENU_ITEMS.at(i);
			SetConsoleTextAttribute(hConsole, 0x07);
			cout << (i == selected_item ? "]" : " ");
			cout << endl;
		}
		key = _getch();
		//cout << (int)key << endl;
		switch (key)
		{
		case UP_ARROW:	 /*if (selected_item > 1)*/selected_item--; break;
		case DOWN_ARROW: /*if (selected_item < MENU_ITEMS.size())*/selected_item++; break;
		case Enter:		 return selected_item;
		case Escape:	 return 0;
		}
		if (selected_item == MENU_ITEMS.size() + 1)selected_item = 1;
		if (selected_item == 0)selected_item = MENU_ITEMS.size();
		system("CLS");
	} while (key != Escape);
	return 0;
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for
		(
			std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
			map_it != base.end();
			++map_it
			)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin();
			it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
	cout << "Количество номеров в базе:" << base.size() << endl;
	system("PAUSE");
}

void save(const std::map<std::string, std::list<Crime>>& base, const std::string filename)
{
	std::ofstream fout(filename);
	//fout << delimiter << endl;
	for
		(
			std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
			map_it != base.end();
			++map_it
			)
	{
		fout << map_it->first << ":\t";
		for (std::list<Crime>::const_iterator it = map_it->second.begin();
			it != map_it->second.end(); ++it)
		{
			fout << *it << ",";
		}
		//fout.seekp(-1, std::ios::cur);
		//Метод seekp(offset, direction) задает позицию курсора записи (з - put) -1 смещение на 1 символ обратно
		// std::ios::cur - показывает, что смещение происходит от текущей позиции курсора
		//fout << ";\n";
		fout << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}

std::map<std::string, std::list<Crime>> load(const std::string& filename)
{
	std::map<std::string, std::list<Crime>> base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string license_plate;
			std::getline(fin, license_plate, ':');
			license_plate.erase(0, license_plate.find_first_not_of('n'));
			fin.ignore();	//:

			std::string crimes;
			std::getline(fin, crimes);
			char* sz_buffer = new char[crimes.size() + 1] {};
			strcpy(sz_buffer, crimes.c_str());
			char delimiters[] = ",";
			Crime crime(0, "place", "00:00 01.01.2000");
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				std::cout << pch << "\t";
				//std::string s_crime(pch);
				std::stringstream ss_crime(pch, std::ios_base::in | std::ios_base::out);
				ss_crime >> crime;
				base[license_plate].push_back(crime);
			}
			cout << endl;
			delete[] sz_buffer;
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	return base;
}

void add_crime(std::map<std::string, std::list<Crime>>& base)
{
	int id;
	std::string license_plate;
	std::string place;
	std::string time;
	cout << "Введите номер нарушения: "; cin >> id;
	cout << "Введите номер автомобиля: "; cin >> license_plate;
	cout << "Введите место нарушения: "; cin >> place;
	cout << "Введите время и дату нарушения: "; cin >> time;
	base[license_plate].push_back(Crime(id, place, time));
}

void print_by_number(const std::map<std::string, std::list<Crime>>& base)
{
	std::string license_plate;
	cout << "Введите номер автомобиля: "; cin >> license_plate;
	try
	{
		for (std::list<Crime>::const_iterator it = base.at(license_plate).begin(); it != base.at(license_plate).end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Номера нет в базе" << endl;
	}
	system("PAUSE");
}