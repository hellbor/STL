#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<iterator>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
#define STL_LIST

template<typename T>void vector_info(const std::vector<T>& vec);

void main()
{
	setlocale(LC_ALL, "");
	//cout << "Hello STL" << endl;

#ifdef STL_ARRAY

	const int N = 5;
	std::array<int, N> arr = {3,5,8,13,21};
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

#endif // STL_ARRAY

#ifdef STL_VECTOR
	std::vector<int> vec = { 0,1,1,2,3,5,8,13,21,34 };
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.push_back(55);
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec.at(i) << tab;
	}
	cout << endl;
	vector_info(vec);
	vec.reserve(24);

	//vec.shrink_to_fit();

	vector_info(vec);
	vec.resize(8);
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	vector_info(vec);
	//vec.resize(14);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

	vec.insert(vec.begin() + 4, { 1024,2048,3072,4096 });
	for (int i : vec)cout << i << tab; cout << endl;

	int index;
	int count;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите количество добавляемых элементов: "; cin >> count;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	//vec.insert(vec.begin() + index, value);
	vec.insert(vec.begin() + index, count, value);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	cout << "Введите количество удаляемых элементов: "; cin >> count;
	vec.erase(vec.begin() + index, vec.begin() + index + count);
	for (int i : vec)cout << i << tab; cout << endl;
	vector_info(vec);

#endif // STL_VECTOR

#ifdef STL_LIST
	std::list<int>list = { 3,5,8,13,21 };
	/*for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;*/
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it)
		cout << *it << tab;
	cout << endl;
	cout << list.front() << endl;
	cout << list.back() << endl;
	list.push_front(2);
	list.push_back(34);
	list.emplace_front(1);
	for (int i : list)cout << i << tab; cout << endl;

	int index;
	int value;
	do
	{
		cout << "Введите индекс добавляемого элемента: "; cin >> index;
		if (index >= list.size())cout << "Error: Out of range" << endl;
	} while (index >= list.size());
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	std::list<int>::iterator position = list.begin();
	//for (int i = 0; i < index; i++)position++;
	std::advance(position, index);
	list.insert(position, value);
	for (int i : list)cout << i << tab; cout << endl;
#endif // STL_LIST

}

template<typename T>void vector_info(const std::vector<T>& vec)
{
	cout << "Size:    " << vec.size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
}