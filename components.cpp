#include <iostream>
#include <vector>
#include <stack>
#include <climits>
using namespace std;

void dfs1 (const vector<vector<int> > &g, vector<bool>* used, vector<int>* order, int v) {
	(*used)[v] = true;
	for (int i = 0; i < g[v].size(); ++i)
		if (!(*used)[ g[v][i] ])
			dfs1 (g, used, order, g[v][i]);
	(*order).push_back (v);
}

void dfs2 (const vector<vector<int> > &gr, vector<bool>* used, vector<int>* component, int v) {
	(*used)[v] = true;
	(*component).push_back (v);
	for (int i = 0; i < gr[v].size(); ++i)
		if (!(*used)[ gr[v][i] ])
			dfs2 (gr, used, component, gr[v][i]);
}

vector<vector<int> > kosaraju(int n, const vector<vector<int> > &g, const vector<vector<int> > &gr)
{
    vector<bool> used;
    used.assign(n, false);
    vector<int> order;
	for (int i = 0; i < n; ++i)
		if (!used[i])
			dfs1(g, &used, &order, i);
    used.assign (n, false);
    vector<vector<int> > result;
    vector<int> component;
    for (int i = n; i >= 0; --i) {
		int v = order[i];
		if (!used[v]) {
			dfs2 (gr, &used, &component, v);
            result.push_back(component);
			component.clear();
		}
	}
    return result;
}

void dfs(int time, const vector<vector<int> > &g, vector<bool>* used, vector<int>* lowlink, stack<int>* st, vector<vector<int> >* result, int v)
{
    (*used)[v] = true;
    (*lowlink)[v] = time++;
    (*st).push(v);
	for (int i = 0; i < g[v].size(); ++i)
        if (!(*used)[g[v][i]])
            dfs(time, g, used, lowlink, st, result, g[v][i]);
    bool isroot = true;
    for (int i = 0; i < g[v].size(); ++i)
        
        if ((*lowlink)[v] > (*lowlink)[g[v][i]]) {
            (*lowlink)[v] = (*lowlink)[g[v][i]];
            isroot = false;
        }
    if (isroot)
    {
        int u;
        vector<int> t;
        (*result).push_back(t);
        do {
            u = (*st).top();
            (*st).pop();
            (*result)[(*result).size() - 1].push_back(u);
            (*lowlink)[u] = INT_MAX;
        } while (u != v);
    }
    
}
vector<vector<int> > tarjan(int n, const vector<vector<int> > &g)
{
    vector<int> lowlink(n, 0);
    vector<bool> used(n, 0);
    stack<int> st;
    vector<vector<int> > result;
    int time = 0;
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs(time, g, &used, &lowlink, &st, &result, i);
    return result;
}

int main()
{
    int n; //количество вершин и ребер
    cin >> n;
    vector<vector<int> > g, gr; //список смежности, прямой и обратный
    vector<int> temp;
    for (int i = 0; i < n; i++)
    {
        g.push_back(temp);
        gr.push_back(temp);
    }
    for (int i = 0; i < n; i++)
    {
        int count; //количество вершин, в которые из текущей ведут ребра
        cin >> count;
        for (int j = 0; j < count; j++)
        {
            int neighbor;
            cin >> neighbor;
            g[i].push_back(neighbor - 1);
            gr[neighbor - 1].push_back(i);
        }
    }
    auto component1 = kosaraju(n, g, gr);
    auto component2 = tarjan(n, g);
    cout << (component1 == component2);
    return 0;
}

