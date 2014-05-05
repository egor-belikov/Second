#include <iostream>
#include <vector>

using namespace std;


vector<int> parent;
vector<int> rk;

class dsu
{
    vector<int> parent, rank;
    
    public:
    
    dsu(int n)
    {
        for (int i = 0; i < n; i++)
        {
            parent.push_back(i);
        }
        rk.assign(n, 0);
    }


    void make_set (int v) {
        parent[v] = v;
        rk[v] = 0;
    }

    int find_set(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set (parent[v]);
    }

    void union_sets (int a, int b) {
        a = find_set (a);
        b = find_set (b);
        if (a != b) {
            if (rk[a] < rk[b])
                swap (a, b);
            parent[b] = a;
            if (rk[a] == rk[b])
                ++rk[a];
        }
    }
};

int main(int argc, const char * argv[])
{
    int n; //количество вершин в графе, пока пустом
    cin >> n;
    int commands; //для удобства попросим сразу количество команд. понятно, что для честного онлайн решения поменять потребуется немногое
    cin >> commands;
    dsu q(n);
    for (int i = 0; i < commands; i++)
    {
        string spec; //ADD — добавить, CONNECTED — запрос
        int x, y; //в обоих запросах подаются оба числа
        cin >> spec >> x >> y;
        x--; y--;
        if (spec == "ADD")
            q.union_sets(x, y);
        else
            if (q.find_set(x) != q.find_set(y))
                cout << "NO\n";
            else
                cout << "YES\n";
    }
}

