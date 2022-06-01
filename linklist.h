#pragma once
#include <iostream>
#include <fstream>

using namespace std;

// один элемент списка смежности графа
struct link
{
    int data;   // метка вершины
    link* next; // указатель на следующую вершину в списке
};

class linklist // список смежных вершин
{
private:

    link* first;             // указатель на 1-й элемент списка

public:

    bool e;                  // признак существовани¤ или отсутстви¤ списка

    // списка пока не существует
    linklist()            // конструктор без параметров
    {
        first = NULL; e = false;
    }

    // добавление элемента
    void additem(int d) {
        link* newlink = new link;      // выдел¤ем пам¤ть
        newlink->data = d;             // запоминаем данные
        newlink->next = first;         // запоминаем значение first
        first = newlink;               // first теперь указывает на новый элемент
    };

    // вывод списка
    void display() {
        link* current = first;           // начинаем с первого элемента
        if (!current) cout << "ѕусто!";
        while (current)                 // пока есть данные
        {
            cout << current->data << ' '; // печатаем данные
            current = current->next;       // двигаемс¤ к следующему элементу
        }
    };

    // проверка вхождения элемента в список
    bool exist(int x) {
        link* current = first;           // начинаем с первого элемента
        if (!current) return 0;
        while (current)                 // пока есть данные
        {
            if (current->data == x)
            {
                return 1;
                break;
            }
            current = current->next;       // двигаемс¤ к следующему элементу
            if (current == NULL)
                return 0;
        }
    };

    // опустошение списка
    void makenull() {
        link* current = first;           // начинаем с первого элемента
        link* deleted;
        while (current)                 // пока не достигнут последний элемент
        {
            deleted = current;           //запоминаем указатель на очередной элемент
            current = current->next;      // двигаемс¤ к следующему элементу
            delete deleted;               // удал¤ем  тот, который запомнили 
        }
        first = NULL;
    };

    //Удаление элемента
    void del(int x) {
        link* current = first->next;
        link* past = first;

        if (x == first->data) {
            first = current;
            delete past;
            return;
        }

        while (current->data != x) {
            past = current;
            current = current->next;
        }
        past->next = current->next;
        delete current;
    }

    //Сохранение элементов списка смежности
    void save(int i) {
        link* current = first;
        ofstream File("Graph.txt", ios_base::app);      //создаём файл с записью с конца

        File << i << " ";     //i - это вершина
        while (current) {
            File << current->data << " ";
            current = current->next;
        }       //обычная запись связей в файл
        File << endl;       //отступ для новой вершины

        File.close();
    }
};


