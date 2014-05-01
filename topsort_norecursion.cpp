#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct dfs //будем имитировать рекурсию
{
    int current; //вершина, в которой мы сейчас находимся
    int i; //счетчик, смотрим, на каком элементе из нашего списка смежности мы остановились
};
int main()
{
    int n, m; //количество вершин и ребер
    cin >> n >> m;
    vector<vector<int>> list; //список смежности
    vector<int> temp;
    for (int i = 0; i < n; i++)
        list.push_back(temp);
    for (int i = 0; i < m; i++)
    {
        int count; //количество вершин, в которые из текущей ведут ребра
        for (int j = 0; j < count; j++)
        {
            int neighbor;
            cout << neighbor;
            list[i].push_back(neighbor - 1);
        }
    }
    vector<int> color; //0 — белый, 1 — серый, 2 — черный
    for (int i = 0; i < n; i++)
        color.push_back(0);
    stack<dfs> imitation; //имитируем программный стек
    int i = 0;
    vector<int> result;
    while ((i < n) || (!imitation.empty()))
    {
        if (imitation.empty())//если в стеке ничего нет, попытаемся снова запустить псевдорекурсию
        {
            if (color[i] == 0) //если текущая необработанная вершина не поучаствовала в dfs
            {
                dfs t;
                t.i = 0;
                t.current = i;
                imitation.push(t); //запустим от нее псевдорекурсию
                continue;
            }
            i++;
        }
        else
        {
            color[imitation.top().current] = 1; //покрасим вершину в серый
            if (imitation.top().i == list[imitation.top().current].size()) //проверим, сходили ли мы по всем ребрам
            {
                result.push_back(imitation.top().current); //добавим в массив результата
                color[imitation.top().current] = 2; // покрасим вершину в черный
                imitation.pop(); //выкинем из рекурсии, закончим выполнение
                continue;
            }
            if (color[list[imitation.top().current][imitation.top().i]] == 1) //если мы можем сходить в серую, то говорим, что граф неправильный
                throw runtime_error("Cycle is in graph");
            if (color[list[imitation.top().current][imitation.top().i]] == 2) //если счетчик указывает на ребро, ведущее в уже обработанную вершину, то идем мимо
            {
                imitation.top().i++;
                continue;
            }
            if (color[list[imitation.top().current][imitation.top().i]] == 0) //если можем пойти в непосещенную вершину
            {
                dfs t;
                t.i = 0;
                t.current = list[imitation.top().current][imitation.top().i]; //добавляем в рекурсию
                imitation.push(t);
                continue;
            }
        }
    }
    for (int i = 0; i < result.size(); i++) //выводим результат
        cout << result[i] + 1 << " ";
    cout << endl;
    return 0;
}

