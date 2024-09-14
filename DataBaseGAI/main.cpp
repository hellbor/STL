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
		std::pair<int,std::string>(521,"���������� ������������� �������� ��������"),
		std::pair<int,std::string>(521,"�������� � ������������ �����"),
		std::pair<int,std::string>(229,"���� �� ����������� ������ ���������"),
		std::pair<int,std::string>(229,"��������� ������ ��������� �����"),
		std::pair<int,std::string>(229,"�������� � ������������ �����"),
		std::pair<int,std::string>(325,"����� � ����������� �����"),
		std::pair<int,std::string>(325,"��������� ������ ����������� ��������� ��������� ��"),
		std::pair<int,std::string>(405,"��������� ������ ���������� ������� ������������"),
		std::pair<int,std::string>(405,"���������� ������������� �������� ��������"),
		std::pair<int,std::string>(405,"����������� ����-����� �� ����������� ������ ���������"),
		std::pair<int,std::string>(377,"���������� ������������� �������� ��������"),
		std::pair<int,std::string>(377,"���� �� ����������� ������ ���������"),
		std::pair<int,std::string>(147,"���������� ������������� �������� ��������"),
		std::pair<int,std::string>(147,"������������ ���������� �� ������������ ����������� ���������� ��"),
		std::pair<int,std::string>(228,"�������� � ������������ �����"),
		std::pair<int,std::string>(228,"������� ���������� ����������� �������� ��� ����"),
		std::pair<int,std::string>(756,"���������� ������������� �������� ��������"),
	};

	for (std::map<int, std::string>::iterator it = offence.begin(); it != offence.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}

	int n;
	cout << "������� ����� ����������: "; cin >> n;
	for (std::map<int, std::string>::iterator it = offence.begin(); it != offence.end(); ++it)
		cout << n << endl;
#endif // DATA_BASE_GAI

}