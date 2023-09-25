#include <iostream>
#include <ctime>
using namespace std;

class Node {
public:
	double data;
	Node* prev, * next;

public:
	Node(double data) {
		this->data = data;
		this->prev = this->next = NULL;
	}
};

class LinkedList {
public:
	Node* head, * tail;

	LinkedList() {
		this->head = this->tail = NULL;
	}

	Node* push_back(double data) { //1.добавление в конец списка
		Node* ptr = new Node(data);

		ptr->prev = tail;
		if (tail != NULL)
			tail->next = ptr;
		if (head == NULL)
			head = ptr;
		tail = ptr;

		return ptr;
	}

	Node* push_front(double data) { //2.добавление в начало списка

		Node* ptr = new Node(data);

		ptr->next = head;
		if (head != NULL)
			head->prev = ptr;
		if (tail == NULL)
			tail = ptr;
		head = ptr;

		return ptr;
	}
	void pop_back() { //3.удаление последнего элемента
		if (tail == NULL) return;

		Node* ptr = tail->prev;
		if (ptr != NULL)
			ptr->next = NULL;
		else
			head = NULL;

		delete tail;
		tail = ptr;
	}
	void pop_front() { //4.удаление первого элемента
		if (head == NULL) return;

		Node* ptr = head->next;
		if (ptr != NULL)
			ptr->prev = NULL;
		else
			tail = NULL;

		delete head;
		head = ptr;
	}

	Node* insert(int index, double data) { //5.вставка нового элемента в позицию с индексом
		Node* right = getAt(index);
		if (right == NULL)
			return push_back(data);

		Node* left = right->prev;
		if (left == NULL)
			return push_front(data);

		Node* ptr = new Node(data);

		ptr->prev = left;
		ptr->next = right;
		left->next = ptr;
		right->prev = ptr;

		return ptr;
	}
	Node* getAt(int index) { //6.доступ к произвольному элементу двусвязного списка
		Node* ptr = head;
		int n = 0;

		while (n != index) {
			if (ptr == NULL)
				return ptr;
			ptr = ptr->next;
			n++;
		}
		return ptr;
	}
	void erase(int index) { //7.удаление элемента по индексу
		Node* ptr = getAt(index);
		if (ptr == NULL)
			return;

		if (ptr->prev == NULL) {
			pop_front();
			return;
		}

		if (ptr->next == NULL) {
			pop_back();
			return;
		}

		Node* left = ptr->prev;
		Node* right = ptr->next;
		left->next = right;
		right->prev = left;

		delete ptr;
	}
	int getCount() //8.получение размера списка
	{
		int count = 0;

		Node* current = head;
		while (current != NULL)
		{
			count++;
			current = current->next;
		}
		return count;
	}
	void eraseList() { //9.удаление всех элементов списка
		if (head == NULL) return;

		Node* ptr;
		while (head != NULL) {
			ptr = head;
			head = head->next;
			delete ptr;
		}
	}
	void replace(int index, double data) { //10.замена элемента по индексу на передаваемый элемент
		if (getAt(index) == NULL)
			return;

		erase(index);
		insert(index, data);
		return;
	}
	void listEmpty() { //11.проверка на пустоту списка
		int length = getCount();
		if (length == 0) {
			cout << "Список пустой" << endl;
		}
		else cout << "Список не пустой" << endl;
	}

	void InsertList(int index, LinkedList list) { //13.вставка другого списка в список, начиная с индекса
		Node* ptr = getAt(index);
		ptr->prev->next = list.head;
		list.head->prev = ptr->prev;
		ptr->prev = list.tail;
		list.tail->next = ptr;
	}

	void PushBackList(LinkedList list) { //14.вставка другого списка в конец
		tail->next = list.head;
		list.head->prev = tail;
		tail = list.tail;
	}

	void PushFrontList(LinkedList list) { //15.вставка другого списка в начало
		list.tail->next = head;
		head->prev = list.tail;
		head = list.head;
	}
	void listInlist(bool check) {
		if (check)cout << "Список был вставлен в список" << endl;
		else cout << "Вставки списка в список не было" << endl;
	}

	bool IsEnterForIndex(Node* ptr, LinkedList list2) { //16.проверка на содержание другого списка в списке
		Node* tmp = list2.head;
		while (tmp != NULL && tmp->data == ptr->data) {
			tmp = tmp->next;
			ptr = ptr->next;
		}
		if (tmp == NULL) { return true; }
		else { return false; }
	}

	int enterFirst(LinkedList list2) { //17.поиск первого вхождения другого списка в список
		Node* ptr = head;
		int index = -1;
		for (int i = 0; i <= getCount() - list2.getCount(); i++) {
			if (IsEnterForIndex(ptr, list2)) { return i; }
			ptr = ptr->next;
		}
		return -1;
	}

	int enterLast(LinkedList list2) { //18.поиск последнего вхождения другого списка в список
		Node* ptr = head;
		int index = -1;
		for (int i = 0; i <= getCount() - list2.getCount(); i++) {
			if (IsEnterForIndex(ptr, list2)) { index = i; }
			ptr = ptr->next;
		}
		return index;
	}

	void swap(int index1, int index2) { //19.обмен двух элементов списка по индексам
		double tmp_data = getAt(index1)->data;
		getAt(index1)->data = getAt(index2)->data;
		getAt(index2)->data = tmp_data;
	}
};

void printList(LinkedList list) //вывод списка
{
	cout << "Список: " << endl;
	for (Node* ptr = list.head; ptr != NULL; ptr = ptr->next)
		cout << ptr->data << " " << endl;
}
void printListReverse(LinkedList list) //12.меняет порядок элементов в списке на обратный
{
	cout << "Список: " << endl;
	for (Node* ptr = list.tail; ptr != NULL; ptr = ptr->prev)
		cout << ptr->data << " " << endl;
}


int main()
{
	setlocale(LC_ALL, "rus");
	int x, index, index2, firstElem, choiceBegin, choice_one;
	int lengthBegin = 0;
	bool check = false;
	Node* head = NULL;
	LinkedList list, list2;
	cout << "Введите список, который будет служить вставным" << endl << endl;
	if (lengthBegin == 0)
	{
		cout << "Введите первый элемент для добавления в список: ";
		cin >> firstElem;
		list2.push_back(firstElem);
		lengthBegin++;
		printList(list2);
	}
	do {
		cout << "-----------------------------------------" << endl;
		cout << "Выберите действие: " << endl;
		cout << "1. Добавить элемент в конец списка" << endl;
		cout << "0. Если ввод закончен" << endl;
		cout << "-----------------------------------------" << endl;
		cin >> choiceBegin;
		switch (choiceBegin)
		{
		case 1:
			int lastElem;
			cout << "Введите элемент для добавления: ";
			cin >> lastElem;
			list2.push_back(lastElem);
			printList(list2);
			break;
		}
	} while (choiceBegin != 0);

	while (20) {
		cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~МЕНЮ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		cout << "Выберите команду: \n";
		cout << "\t 1.добавление в конец списка\n";
		cout << "\t 2.добавление в начало списка\n";
		cout << "\t 3.удаление последнего элемента\n";
		cout << "\t 4.удаление первого элемента\n";
		cout << "\t 5.вставка нового элемента в позицию с индексом \n";
		cout << "\t 6.доступ к произвольному элементу двусвязного списка \n";
		cout << "\t 7.удаление элемента по индексу \n";
		cout << "\t 8.получение размера списка \n";
		cout << "\t 9.удаление всех элементов списка\n";
		cout << "\t 10.замена элемента по индексу на передаваемый элемент\n";
		cout << "\t 11.проверка на пустоту списка\n";
		cout << "\t 12.меняет порядок элементов в списке на обратный\n";
		cout << "\t 13.вставка другого списка в список, начиная с индекса\n";
		cout << "\t 14.вставка другого списка в конец\n";
		cout << "\t 15.вставка другого списка в начало\n";
		cout << "\t 16.проверка на содержание другого списка в списке\n";
		cout << "\t 17.поиск первого вхождения другого списка в список\n";
		cout << "\t 18.поиск последнего вхождения другого списка в список \n";
		cout << "\t 19.обмен двух элементов списка по индексам\n";
		cout << "\t 20.ВЫХОД\n";
		cin >> choice_one;
		switch (choice_one) {
		case 1:
			cout << "Введите элемент: \n";
			cin >> x;
			list.push_back(x);
			printList(list);
			break;
		case 2:
			cout << "Введите элемент: \n";
			cin >> x;
			list.push_front(x);
			printList(list);
			break;
		case 3:
			list.pop_back();
			printList(list);
			break;
		case 4:
			list.pop_front();
			printList(list);
			break;
		case 5:
			cout << "Введите индекс: \n";
			cin >> index;
			cout << "Введите элемент: \n";
			cin >> x;
			list.insert(index, x);
			printList(list);
			break;
		case 6:
			cout << "Введите индекс: \n";
			cin >> index;
			cout << "Найденный элемент: " << list.getAt(index)->data;
			break;
		case 7:
			cout << "Введите индекс: \n";
			cin >> index;
			list.erase(index);
			printList(list);
			break;
		case 8:
			cout << "Размер списка: " << list.getCount() << endl;
			break;
		case 9:
			list.eraseList();
			printList(list);
			break;
		case 10:
			cout << "Введите индекс: \n";
			cin >> index;
			cout << "Введите элемент: \n";
			cin >> x;
			list.replace(index, x);
			printList(list);
			break;
		case 11:
			list.listEmpty();
			break;
		case 12:
			printListReverse(list);
			break;
		case 13:
			if (check) {
				cout << "Вставка уже была реализована";
			}
			else {
				check = true;
				cout << "Введите индекс: \n";
				cin >> index;
				list.InsertList(index, list2);
				printList(list);
			}
			break;
		case 14:
			if (check) {
				cout << "Вставка уже была реализована";
			}
			else {
				check = true;
				list.PushBackList(list2);
				printList(list);
			}
			break;
		case 15:
			if (check) {
				cout << "Вставка уже была реализована";
			}
			else {
				check = true;
				list.PushFrontList(list2);
				printList(list);
			}
			break;
		case 16:
			if (list.enterFirst(list2) != -1) {
				cout << "Список содержится в исходном" << endl;
			}
			else {
				cout << "Список не содержится в исходном" << endl;
			}
			break;
		case 17:
			index = list.enterFirst(list2);
			if (index != -1) {
				cout << "Первое вхождение списка в список (индекс): " << index << endl;
			}
			else {
				cout << "Вхождений нет." << endl;
			}
			break;
		case 18:
			index = list.enterLast(list2);
			if (index != -1) {
				cout << "Последнее вхождение списка в список (индекс): " << index << endl;
			}
			else {
				cout << "Вхождений нет." << endl;
			}
			break;
		case 19:
			cout << "Введите индекс первого элемента: \n";
			cin >> index;
			cout << "Введите индекс второго элемента: \n";
			cin >> index2;
			list.swap(index, index2);
			printList(list);
			break;
		case 20:
			exit(20);
			break;
		default:
			cout << "\nУказана неверная цифра\n";
		}
	}
}