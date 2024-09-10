#include<iostream>
#include<array>
#include<vector>
#include<stack>
using std::cin;
using std::cout;
using std::endl;;

#define tab "\t"

class Element
{
protected:
	int Data;			//�������� ��������
	Element* pNext;		//��������� �� ��������� �������
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0;

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	Element* Head;
	unsigned int size;
public:

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	//					Constructors:

	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other;
		cout << "LCopyConstructor:" << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept :ForwardList()
	{
		/*this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;*/
		*this = std::move(other);
		cout << "LMoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		/*while (Head)pop_front();
		pop_back();*/
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		reverse();
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other)return *this;
		//delete[]this->Head;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "LMoveAssignment:\t\t" << this << endl;
		return *this;
	}

	//				Adding elements:
	void push_front(int Data)
	{
		////1) ������� ����� �������:
		//Element* New = new Element(Data);
		////2) �������� ����� ������� � ������:
		//New->pNext = Head;
		////3) ��������� ������ �� ����� �������:
		//Head = New;

		Head = new Element(Data, Head);
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}

		////2) ������� ����� �������:
		//Element* New = new Element(Data);
		////3) �������� ����� ������� � ������:
		//Temp->pNext = New;

		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)return;
		if (Index == 0)return push_front(Data);
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head;	//1)���������� ����� ���������� ��������
		Head = Head->pNext;		//2)������� ������ �� ��������� �������
		delete erased;			//3)������� ������� �� ������
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr)return pop_front();

		//1)������� �� �������������� �������� ������
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;

		//2) ������� ��������� ������� �� ������:
		delete Temp->pNext;

		//3) �������� ��������� �� ��������� �������:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();

		//1) ������� �� �������� ����� ���������:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//2) ���������� ����� ���������� ��������:
		Element* erased = Temp->pNext;

		//3) ��������� ��������� ������� �� ������:
		Temp->pNext = Temp->pNext->pNext;

		//4) ������� ������� �� ������:
		delete erased;
		size--;
	}

	//					Methods:

	void reverse()
	{
		ForwardList buffer;
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}

	void print()const
	{
		cout << "Head:\t" << Head << endl;
		//Element* Temp = Head;	//Temp - ��� ��������.
		////�������� - ��� ���������, ��� ������ �������� ����� ���������� ��������� ������
		//while (Temp)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext; //������� �� ��������� �������
		//}
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;;
		cout << "���������� ��������� ������: " << size << endl;
		cout << "����� ���������� ��������� ������: " << Element::count << endl;
		//cout << "����� ���������� ��������� ������: " << Head->count << endl;
	}
};

template<typename T> class Stack :public std::stack<T>
{
	typedef std::stack<T> base_type;
	typedef typename base_type::container_type container_type;
public:
	using base_type::stack;
	typedef typename container_type::reverse_iterator iterator;
	typedef typename container_type::const_reverse_iterator const_iterator;

	iterator begin() 
	{ 
		return this->c.rbegin(); 
	}
	iterator end()
	{
		return this->c.rend(); 
	}
template<typename T>
	stack<T>::iterator begin(const stack<T>& s)
{
	return s.begin();
}

template<typename T>
	stack<T>::iterator end(const stack<T>& s)
{
	return s.end();
}
};


void Print(int arr[])
{
	cout << typeid(arr).name() << endl;
	cout << sizeof(arr) << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
	/*for (int : arr)
	{
		cout << i << tab;
	}
	cout << endl;*/
}

//template<typename T> stack

//#define BASE_CHECK
//#define COUNT_CHECK
//#define LIST_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define STACK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.print();
	//list.pop_back();
	//list.print();

	int index;
	int value;
	cout << "������� ������ ������ ��������: "; cin >> index;
	cout << "������� �������� ������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

#endif // COUNT_CHECK

#ifdef LIST_CHECK
	int n;
	cout << "������� ���������� ���������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	cout << "List filled" << endl;
	list.print();

	cout << "Making copy" << endl;
	ForwardList list2 = list;				//CopyConstructor
	//ForwardList list2;
	//list2 = list;
	list2.print();
	cout << "Copy DONE" << endl;

	ForwardList list3 = std::move(list2);	//MoveConstructor
	list3.print();

#endif // LIST_CHECK

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21,34,55,89,144 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	//Ranged-based for:
	//Range (��������) � ������ ������ ���������� ��� ���������
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

#ifdef STACK
	std::stack<int>stk = { };
	stk.push(3);
	stk.push(5);
	stk.push(8);
	stk.push(13);
	stk.push(21);
	
	for (int i : stk)
	{
		cout << i << tab;
	}
	cout << endl;
	//stack_info(stk);
#endif // STACK

}