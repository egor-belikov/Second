#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000
using namespace std;

int main()
{
    int a[MAXN], b[MAXN]; //здесь оба массива ввода
    int dynamic[MAXN][MAXN]; //массив для подсчёта динамики
    int previous[MAXN]; //массив для восстановления ответа
    for (int i = 0; i < MAXN; i++)
        previous[i] = -1; //заполним массив для восстановления ответа
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i];
    for (int j = 0; j < m; j++)
        dynamic[0][j] = (int)(a[0] == b[j]); //заполним первую строчку. инициалзиация динамики
    for (int i = 1; i < n; i++) //динамика такая. d[i][j] — это длина наибольшей возрастающей общей подпоследовательности префиксов a[1..i] и b[1..j], притом что b[j] — последний элемент в этой НОВП. Для очередной d[i][j] есть два варианта:
    {
        int index = -1, best = 0;
        for (int j = 0; j < m; j++)
        {
            dynamic[i][j] = dynamic[i - 1][j];
            if ((a[i] == b[j]) && (dynamic[i - 1][j] < best + 1)) //a[i] входит в НОВП. Тогда просто обновим динамику из значения best, прибавив 1. best обновляется дальше
            {
                dynamic[i][j] = best + 1;
                previous[j] = index;
            }
            if ((a[i] > b[j]) && (dynamic[i - 1][j] > best)) //a[i] не входит в НОВП. Тогда посмотрим, нужно ли обновлять best для следующего ряда d[i].
            {
                best = dynamic[i - 1][j];
                index = j;
            }
            
        }
    }
    int position = 0;
    for (int j = 0; j < m; j++) //восстановление ответа очевидно.
        if (dynamic[n - 1][position] < dynamic[n - 1][j])
            position = j;
    vector<int> result;
    while (position != -1)
    {
        result.push_back(b[position]);
        position = previous[position];
    }
    cout << result.size() << endl;
    reverse(result.begin(), result.end());
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << " ";
    cout << endl;
    return 0;
}

