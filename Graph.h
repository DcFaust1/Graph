#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>
#include "linklist.h"

using namespace std;

class Graph
{
private:

	linklist adj[100];   // 100 - ограничение максимального числа вершин

public:
	bool E(int x) {
		if (adj[x].e) return 1;
		else return 0;
	}

	bool Exist(int x, int y) {
		return adj[x].exist(y);
	}

	void AddVertex(int x) {
		if (adj[x].e == false) adj[x].e = true;
		else cout << "Такая вершина уже есть !!!" << endl;
	};       // добавление вершины в граф

	void AddEdge(int x, int y) {
		if (adj[x].e == true && adj[y].e == true && adj[x].exist(y) == false && (x != y))
		{
			adj[x].additem(y);
		}
		else cout << "Ошибка добавления ребра!" << endl;
	}; // добавление ребра в граф

	void Display() {
		for (int i = 1; i < 100; i++)
		{
			if (adj[i].e == true)
			{
				cout << i << " - ";
				adj[i].display();
				cout << endl;
			}
		}
	};          // вывод списка смежности графа

	void DelEdge(int x, int y) {
		if (!adj[x].e || !adj[y].e) {
			cout << "Ошибка!\n";
			return;
		}//Если нет списков у двух этих вершин, то нам делать нечего
		if (adj[x].exist(y)) {
			adj[x].del(y);
			cout << "Ребро удалено!\n";
		}
		else cout << "Нет такого ребра!\n";
	};		//Удаление ребра

	void DelVertex(int x) {
		if (!adj[x].e) {
			cout << "Нет такой вершины!\n";
			return;
		}
		adj[x].makenull();
		adj[x].e = 0;
		for (int i = 0; i < 100; i++) {
			if (adj[i].e)
				if (adj[i].exist(x)) adj[i].del(x);
		}
	};		//Удаление вершины

	void SaveGraph() {
		ofstream File("Graph.txt", ios_base::trunc);
		File.close();
		for (int i = 0; i < 100; i++) {
			if (adj[i].e) adj[i].save(i);
		}
	}       //Если есть вершина, то переходим в сохранение внутренностей

	void LoadGraph() {
		ifstream file("Graph.txt", ios::in);
		char ch, ch1;
		int a = 0, b = 0;

		if (!file.is_open()) {
			cout << "Ошибка загрузки!\n";
			return;
		}

		while (file >> ch) {
			ch1 = file.get();
			a = ch - 48;
			while (ch1 > 48 && ch1 < 58) {
				b = ch1 - 48;
				a = a * 10 + b;
				ch1 = file.get();
			}
			adj[a].e = true;
			while (ch1 != '\n' && ch != '\n') {
				if (ch1 > 48 && ch1 < 58) {
					b = ch1 - 48;
					ch = file.get();
					while (ch > 48 && ch < 58) {
						b = b * 10 + ch - 48;
						ch = file.get();
					}
					adj[a].additem(b);
				}
				ch1 = file.get();
			}
		}

		file.close();

		cout << "Граф загружен!\n";
	}

	void First(int x) {
		if (!adj[x].e) {
			cout << "Нет такой вершины!\n";
			return;
		}       //Проверка на наличие вершины

		queue <int> q;      //Создаём очередь
		vector<bool> b(100, false);        //Массив пройденных вершин
		int v;

		q.push(x);      //Добавляем x в очередь
		b[x] = true;        //Отмечаем вершину как уже посещённую

		cout << "Пройденные вершины:\n";

		while (!q.empty()) {        //Выполняем пока не закончится очередь
			v = q.front();      //Берём первый элемент
			q.pop();        //Стираем первый элемент в очереди
			cout << v << " ";       //Вывод пройденных вершин
			for (int i = 0; i < 100; i++) {
				if (adj[v].exist(i) && !b[i]) {     //Если вершина связана с рассматриваемой и не посещена
					b[i] = true;
					q.push(i);
				}
			}
		}
	}

	void OstDerevo(Graph G, int x) {
		stack <int> q;      //Создаём стек
		vector <bool> b(100, false);        //Массив пройденных вершин

		int v;
		q.push(x);      //Добавляем v в стек
		b[x] = true;        //Отмечаем вершину как уже посещённую

		while (!q.empty()) {        //Выполняем пока не закончится стек
			v = q.top();      //Берём первый элемент
			q.pop();        //Стираем первый элемент в стеке
			if (!this->adj[v].e) this->AddVertex(v);        //Создаём вершину
			for (int i = 0; i < 100; i++) {
				if (G.adj[v].exist(i) && !b[i]) {     //Если вершина связана с рассматриваемой и не посещена
					b[i] = true;
					q.push(i);
					if (!this->adj[i].e) this->AddVertex(i);
					this->AddEdge(i, v);
				}
			}
		}
	}
};

