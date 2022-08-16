#include<iostream>
#include<string>
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();

	void pop_front();
	void push_back(T data);             // прототип метода добавления в конец списка
	void clear();
	int GetSize() { return Size; }
	T& operator[](const int index);     // перегрузка оператора квадратных скобочек. Возвращаем ссылку на тип Т, чтобы имень возможность их изменять. Индекс номер эллемента который хотим вернуть
	void push_front(T data);
	void insert(T value, int index);
	void removeAt(int index);
	void pop_back();

private:

	template<typename T>       // шаблонный класс
	class Node                 // узел
	{
	public:
		Node* pNext;          // указатель на следующий элемент
		T data;               // данные

		Node(T data = T(), Node* pNext = nullptr) // конструктор, присваивает значения по умолчанию
		{
			this->data = data;                    // присваеваем входящме параметры соотв. полям
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T> *head;                                // указатель на голову типа node 
};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;                              // нумирация списка с 0, чтобы быть уверенными
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;                   // временной переменной присваеваем голову
	head = head->pNext;                     // голове присваеваем следующий элемент
	delete temp;                            // удаляем первую переменную из временной
	Size--;
}

template<typename T>
void List<T>::push_back(T data)                  // создание и добавления нового элемента в конец
{
	if (head == nullptr)                         // проверяем есть ли что-то а заголовке
	{
		head = new Node<T>(data);                // если он пустой, то создаём новый эллемент Node и передаём ему данные
	}
	else
	{
		Node<T>* current = this->head;           // в текущий элеммент с которым мы работаем присваевам адрес нашего хедера
		while (current->pNext != nullptr)        // проверяем на что указывает pNext
		{
			current = current->pNext;            // присваеваем указатель на следующий эллемент, пока не дойдём до null
		}
		current->pNext = new Node<T>(data);      // создаём новый эллемент и присваеваем адрес дин. памяти ноде указатнлю на null
	}
	Size++;
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
T& List<T>::operator[](const int index)
{	
	int counter = 0;                        // счётчик элемента в котором находимся

	Node<T>* current = this->head;          // временный обьект каррент(отвечает за то, в какой конкретно ноде, в каком конкретно эллементе мы находимся, чтобы проверить адрес следующего)

	while (current != nullptr)              // пока указатель на текущий эллемент не равен null
	{
		if (counter == index)               // проверяем совпадает ли значение счётчика с индексом который мы ищем
		{
			return current->data;           // возвращаем данные из поля дата
		}
		current = current->pNext;           // присваеваем адрес следующего эллемента
		counter++;
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void List<T>::insert(T data, int index)
{
	if (index==0)
	{
		push_front(data);
	}
	else
	{
		Node<T>* previous = this->head; // создаём временный указатель и присваиваем значение хеда

		for (int i = 0; i < index - 1; i++)  // цикл поиска элемента с индексом предшествующем входящему индексу
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;

		Size++;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head; // создаём временный указатель и присваиваем значение хеда

		for (int i = 0; i < index - 1; i++)  // цикл поиска элемента с индексом предшествующем входящему индексу
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;

		delete toDelete;
		Size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);;
}



int main()
{
	setlocale(LC_ALL, "ru");
	 
	List<int> lst;                          // создаём объект класса лист
	lst.push_back(55);
	lst.push_back(11);
	lst.push_back(22);

	for (int i = 0; i < lst.GetSize(); i++) // если текущий индекс меньше чем кол-во элементов в массиве
	{
		cout << lst[i] << endl;             // вывод всех элементов списка
	}

	cout << endl << endl;

	lst.removeAt(1);

	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << lst[i] << endl;
	}




	//int numbersCount;
	//cin >> numbersCount;
	//for (int i = 0; i < numbersCount; i++)  // цикл заполнения листа
	//{
	//	lst.push_back(rand() % 10);         // генерация псевдослучайных чисел
	//}
	//for (int i = 0; i < lst.GetSize(); i++) // если текущий индекс меньше чем кол-во элементов в массиве
	//{
	//	cout << lst[i] << endl;             // вывод всех элементов списка
	//}
	//cout << lst[3] << endl;

	return 0;
}


