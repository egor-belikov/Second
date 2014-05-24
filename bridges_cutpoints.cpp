#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

void dfs_cutpoints (const vector<vector<int> > &g, vector<int>* tin, vector<int>* fup, set<int>* res, vector<bool>* used, int timer, int v, int p = -1) {
	(*used)[v] = true;
	(*tin)[v] = (*fup)[v] = timer++;
	int children = 0;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if ((*used)[to])
			(*fup)[v] = min ((*fup)[v], (*tin)[to]);
		else {
			dfs_cutpoints (g, tin, fup, res, used, timer, to, v);
			(*fup)[v] = min ((*fup)[v], (*fup)[to]);
			if ((*fup)[to] >= (*tin)[v] && p != -1)
                (*res).insert(v);
            ++children;
		}
	}
	if (p == -1 && children > 1)
        (*res).insert(v);
}

vector<int> cutpoints(const vector<vector<int> > &g)
{
    int n = (int)g.size(), timer = 0;
    vector<int> tin(n, 0), fup(n, 0), vecres;
    set<int> res;
    vector<bool> used(n, false);
    for (int i = 0; i < n; i++)
        if (!used[i])
            dfs_cutpoints(g, &tin, &fup, &res, &used, timer, i);
    for (set<int>::iterator it = res.begin(); it != res.end(); it++)
        vecres.push_back(*it);
    sort(vecres.begin(), vecres.end());
    return vecres;
}

void dfs_bridges (const vector<vector<int> > &g, vector<int>* tin, vector<int>* fup, vector<pair<int, int> >* res, vector<bool>* used, int timer, int v, int p = -1) {
	(*used)[v] = true;
	(*tin)[v] = (*fup)[v] = timer++;
	int children = 0;
	for (size_t i = 0; i < g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue;
		if ((*used)[to])
			(*fup)[v] = min ((*fup)[v], (*tin)[to]);
		else {
			dfs_bridges (g, tin, fup, res, used, timer, to, v);
			(*fup)[v] = min ((*fup)[v], (*fup)[to]);
			if ((*fup)[to] > (*tin)[v])
                (*res).push_back(make_pair(v, to));
            ++children;
		}
	}
}

vector<pair<int, int> > bridges(const vector<vector<int> > &g) {
	int n = g.size(), timer = 0;
    vector<bool> used(n, false);
    vector<int> tin(n, 0), fup(n, 0);
    vector<pair<int, int> > res;
	for (int i = 0; i < n; ++i)
		if (!used[i])
            dfs_bridges(g, &tin, &fup, &res, &used, timer, i);
    return res;
}

void dfs_component_cutpoints(const vector<vector<int> > &g, const set<int> &allcutpoints, vector<vector<int> >* res, vector<bool>* used, int v)
{
    (*used)[v] = true;
    (*res)[(*res).size() - 1].push_back(v);
    for (int i = 0; i < g[v].size(); i++)
        if (!(*used)[g[v][i]] && (allcutpoints.find(g[v][i]) == allcutpoints.end()))
            dfs_component_cutpoints(g, allcutpoints, res, used, g[v][i]);
}
vector<vector<int> > component_cutpoints(const vector<vector<int> > &g)
{
    int n = (int)g.size();
    vector<int> br = cutpoints(g), t;
    vector<bool> used(n, false);
    set<int> allcutpoints;
    vector<vector<int> > res;
    for (int i = 0; i < br.size(); i++)
        allcutpoints.insert(br[i]);
    for (int i = 0; i < n; i++)
        if (!used[i])
        {
            res.push_back(t);
            dfs_component_cutpoints(g, allcutpoints, &res, &used, i);
        }
    return res;
}

void dfs_component_bridges(const vector<vector<int> > &g, const set<pair<int, int> > &allbridges, vector<vector<int> >* res, vector<bool>* used, int v)
{
    (*used)[v] = true;
    (*res)[(*res).size() - 1].push_back(v);
    for (int i = 0; i < g[v].size(); i++)
        if (!(*used)[g[v][i]] && (allbridges.find(make_pair(v, g[v][i])) == allbridges.end()))
            dfs_component_bridges(g, allbridges, res, used, g[v][i]);
}
vector<vector<int> > component_bridges(const vector<vector<int> > &g)
{
    int n = g.size();
    vector<pair<int, int>> br = bridges(g);
    vector<int> t;
    vector<bool> used(n, false);
    set<pair<int, int> > allbridges;
    vector<vector<int> > res;
    for (int i = 0; i < br.size(); i++)
    {
        allbridges.insert(br[i]);
        allbridges.insert(make_pair(br[i].second, br[i].first));
    }
    for (int i = 0; i < n; i++)
        if (!used[i])
        {
            res.push_back(t);
            dfs_component_bridges(g, allbridges, &res, &used, i);
        }
    return res;
}
int main()
{
    vector<vector<int> > a;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        vector<int> t;
        a.push_back(t);
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--; y--;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    vector<int>res = cutpoints(a);
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); i++)
        cout << res[i] + 1 << endl;

    return 0;
}

