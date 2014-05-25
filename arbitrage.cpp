#include <iostream>
#include <vector>
#include <cfloat>
#include <math.h>
#include <algorithm>

using namespace std;

struct edge
{
    int a, b;
    double cost;
};

int n, m;
const double INF = DBL_MAX;

void fordbellman(const vector<edge> &e, int v)
{
    vector<double> d (n, 0);
    d[v] = 1;
    vector<int> p (n, -1);
    int x;
    for (int i=0; i<n; ++i) {
        x = -1;
        for (int j=0; j<m; ++j)
            if (d[e[j].a] > 0)
                if (d[e[j].b] < d[e[j].a] * e[j].cost)
                {
                    d[e[j].b] = min (INF, d[e[j].a] * e[j].cost);
                    p[e[j].b] = e[j].a;
                    x = e[j].b;
                }
        
    }
    if (x == -1)
        cout << "No negative cycle from " << v;
    else
    {
        int y = x;
        for (int i=0; i<n; ++i)
            y = p[y];
        
        vector<int> path;
        for (int cur=y; ; cur=p[cur]) {
            path.push_back (cur);
            if (cur == y && path.size() > 1)  break;
        }
        reverse (path.begin(), path.end());
        
        cout << "Negative cycle: ";
        for (size_t i=0; i<path.size(); ++i)
            cout << path[i] + 1 << ' ';
        cout << endl;
    }
}

void print_cycle(const vector<vector<int> > &r, int x, int y)
{
    if ((r[x][y] == -1) || ((x == r[x][y]) && (x == y)))
        cout << x + 1 << " ";
    else
    {
        print_cycle(r, x, r[x][y]);
        print_cycle(r, r[x][y], y);
    }
}

void floyd(const vector<vector<double> > &d)
{
    vector<vector<double> > a = d;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i < j)
                swap(a[i][j], a[j][i]);
    vector<vector<int> > r;
    for (int i = 0; i < n; i++)
    {
        vector<int> t(n, -1);
        r.push_back(t);
    }
    vector<int> cycle;
    int start;
    bool cycle_exists = false;
    for (int i = 0; (i < n) && cycle_exists; i++)
        for (int j = 0; j < n && cycle_exists; j++)
            for (int k = 0; k < n && cycle_exists; k++)
                if (a[j][i] * a[i][k] > a[j][k])
                {
                    a[j][k] = a[j][i] * a[i][k];
                    r[j][k] = i;
                    if ((j == k) && (a[j][j] > 1))
                    {
                        cycle_exists = true;
                        start = j;
                        break;
                    }
                }
    if (!cycle_exists)
        cout << "No negative cycle\n";
    else
    {
        cout << "Negative cycle: ";
        print_cycle(r, start, start);
        cout << start + 1 << endl;
    }
    
    
}
int main()
{
    vector<vector<double> > a;
    vector<edge> e;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        vector<double> t;
        a.push_back(t);
        for (int j = 0; j < n; j++)
        {
            double tt;
            cin >> tt;
            a[i].push_back(tt);
            edge k;
            k.a = i;
            k.b = j;
            k.cost = tt;
            e.push_back(k);
            m++;
        }
    }
    fordbellman(e, 0);
    floyd(a);
}
