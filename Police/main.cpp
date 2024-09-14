#pragma warning (disable: 4326)
#include<iostream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n------------------------------------------------------------------------------\n"

const std::map<int, std::string> VIOLATION =
{
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
	int violation;
	std::string place;
	std::string time;
public:
	/*const std::string& get_license_plate()const
	{
		return license_plate;
	}*/
	int get_violation_id()const
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
	const std::string& get_time()const
	{
		return time;
	}
	/*void get_license_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	void get_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		this->time = time;
	}

	//					Constructors
	Crime
	(
		int violation_id,
		const std::string& place,
		const std::string& time
	)
	{
		get_violation_id(violation_id);
		set_place(place);
		set_time(time);
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

void main()
{
	setlocale(LC_ALL, "");
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
	for 
		(
			std::map<std::string, std::list<Crime>>::iterator map_it = base.begin();
			map_it != base.end();
			++map_it
		)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::iterator it = map_it->second.begin();
			it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}