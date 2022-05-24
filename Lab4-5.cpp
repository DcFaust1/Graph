// Представление ОРИЕНТИРОВАННОГО графа
#include <iostream>
#include <fstream>
#include "Graph.h"

using namespace std;

void Choice() {
    cout << "Введите цифру: \n" <<
            "1)Создать вершины \n" <<
            "2)Добавить рёбра \n" <<
            "3)Удалить ребро \n" <<
            "4)Удалить вершину \n" <<
            "5)Сохранить граф \n" <<
            "6)Загрузить граф \n" <<
            "7)Показать граф \n" <<
            "8)Показать дополнение к графу\n" <<
            "9)Обход в ширину\n" <<
            "10)Показать остовное дерево графа\n" <<
            "0)Завершить программу \n";
            //Даём выбор действий
}

int main()
{
    setlocale(LC_ALL, "RU");

    int x, y, n, a = 0;
    char sw;

    Graph G;       // создаем переменную-список
    Graph G1;

    Choice();
    cout << endl;
    cin >> a;

    while (a != 0) {
        cout << endl;
        switch (a) {
        case 1:
            cout << "Введите количество вершин графа: " << endl;
            cin >> n;

            while (n > 0)
            {
                cout << "Введите метку очередной  вершины - ";
                cin >> x;
                G.AddVertex(x); // добавляем туда несколько чисел
                n--;
            }
            break;
        case 2:
            sw = 'y';

            while (sw != 'n')
            {
                cout << "Введите соединяемые вершины - (x,y)" << endl;
                cin >> x;
                cin >> y;
                G.AddEdge(x, y); // добавляем туда несколько чисел
                cout << "Хотите ли добавить ещё соединения - (y/n)? " << endl;
                cin >> sw;
            }
            break;
        case 3:
            cout << "Какое ребро хотите удалить? - (x,y)\n";
            cin >> x;
            cin >> y;
            G.DelEdge(x, y);
            break;
        case 4:
            cout << "Какую вершину вы хотите удалить?\n";
            cin >> x;
            G.DelVertex(x);
            break;
        case 5:
            G.SaveGraph();
            cout << "Граф сохранён!\n";
            break;
        case 6:
            G.LoadGraph();
            break;
        case 7:
            G.Display();
            break;
        case 8:
            for (int i = 0; i < 100; i++) {
                if (G.E(i)) G1.AddVertex(i);
            }
            for (int i = 0; i < 100; i++) {
                for (int j = 0; j < 100; j++) {
                    if (G1.E(i) && i != j && G1.E(j))
                        if (!G.Exist(i, j)) G1.AddEdge(i, j);
                }
            }
            G1.Display();
            break;
        case 9:
            cout << "С какой вершины начать?\n";
            cin >> x;
            G.First(x);
            break;
        case 10:
            cout << "С какой вершины начать? ";
            cin >> x;
            G1.OstDerevo(G, x);
            G1.Display();
            return 0;
        }
        cout << endl;
        Choice();
        cout << endl;
        cin >> a;
    }
    return 0;
}
