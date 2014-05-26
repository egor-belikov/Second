#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int s1 = 100, s2 = 10, N = 10, M = 10;
class dsu
{
public:
    vector<int> parent;
    vector<int> rank;
    dsu(int n)
    {
        rank.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    void make_set (int v) {
        parent[v] = v;
        rank[v] = 0;
    }
    
    int find_set (int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find_set (parent[v]);
    }
    
    void union_sets (int a, int b) {
        a = find_set (a);
        b = find_set (b);
        if (a != b) {
            if (rank[a] < rank[b])
                swap (a, b);
            parent[b] = a;
            if (rank[a] == rank[b])
                ++rank[a];
        }
    }
};

struct edge
{
    int a, b;
    double len;
    bool operator< (const edge &other)
    {
        return len < other.len;
    }
};

double len(pair<double, double> a, pair<double, double> b)
{
    return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

class solve
{
public:
    vector<pair<double, double> > points;
    vector<edge> edges, answer;
    vector<int> result;
    vector<bool> visited;
    dsu su;
    vector<vector<int> > a;
    int n;
    pair<double, double> randompoint(int s)
    {
        double x = 0, y = 0;
        int i = 0;
        for (; (x * x + y * y > 1) || (x * x + y * y == 0); i++)
             {
                 x = (double) rand() / RAND_MAX * 2 - 1;
                 y = (double) rand() / RAND_MAX * 2 - 1;
             }
        double t = sqrt(log(x * x + y * y) * (-2) / (x * x + y * y));
        return make_pair(x * t * s, y * t * s);
    }
    
    void gen()
    {
        for (int i = 0; i < N; i++)
        {
            pair<double, double> c = randompoint(s1);
            for (int j = 0; j < M; j++)
            {
                pair<double, double> t = randompoint(s2);
                t.first += c.first;
                t.second += c.second;
                points.push_back(t);
            }
        }
    }
    
    void dfs(int index)
    {
        visited[index] = true;
        result.push_back(index);
        for (int i = 0; i < a[index].size(); i++)
            if (!visited[a[index][i]])
                dfs(a[index][i]);
    }
    
    void all()
    {
        
        gen();
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (i != j)
                {
                    edge t;
                    t.a = i;
                    t.b = j;
                    t.len = len(points[i], points[j]);
                    edges.push_back(t);
                }
        sort(edges.begin(), edges.end());
        for (int i = 0; i < edges.size(); ++i)
            if (su.find_set(edges[i].a) != su.find_set(edges[i].b))
            {
                su.union_sets(edges[i].a, edges[i].b);
                answer.push_back(edges[i]);
            }
        for (int i = 0; i < answer.size(); i++)
        {
            vector<int> t(n, 0);
            a.push_back(t);
        }
        for (int i = 0 ; i < answer.size(); i++)
        {
            
            a[answer[i].a].push_back(answer[i].b);
            a[answer[i].b].push_back(answer[i].a);
        }
        dfs(edges[0].a);
        double counted = 0, stupid = 0;
        for (int i = 0; i < result.size() - 1; i++)
            counted += len(points[result[i]], points[result[i + 1]]);
        for (int i = 0; i < points.size() - 1; i++)
            stupid += len(points[i], points[i + 1]);
        cout.precision(3);
        cout << counted << " " << stupid << endl;
        if (counted <= stupid)
            cout << "OK\n";
        else
            cout << "WA\n";
    }
    solve():
    n(N * M),
    visited(N * M, false),
    su(N * M){};
    
};

int main()
{
    solve q;
    q.all();
}

