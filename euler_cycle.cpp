#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;
int main() {
    
	int n;
    cin >> n;
	vector < set<int> > g;
    set<int> empty;
    for (int i = 0; i < n; i++)
    {
        g.push_back(empty);
        int size;
        cin >> size;
        for (int j = 0; j < size; j++)
        {
            int vertex;
            cin >> vertex;
            g[i].insert(vertex - 1);
            
        }
    }
	vector<int> deg (n);
	for (int i=0; i<n; ++i)
        deg[i] = (int)g[i].size();
    
	int first = 0;
	while (!deg[first])  ++first;
    
	int v1 = -1,  v2 = -1;
	bool bad = false;
	for (int i=0; i<n; ++i)
		if (deg[i] % 2 == 1)
        {
			if (v1 == -1)
            {
				v1 = i;
            }
			else
            {
                if (v2 == -1)
                    v2 = i;
                else
                    bad = true;
            }
        }
	stack<int> st;
	st.push (first);
	vector<int> res;
	while (!st.empty())
	{
		int v = st.top();
		int i;
		for (i=0; i<n; ++i)
            if (g[v].find(i) != g[v].end())
                break;
		if (i == n)
		{
			res.push_back (v);
			st.pop();
		}
		else
		{
            g[v].erase(i);
            g[i].erase(v);
			st.push (i);
		}
	}
    
	for (int i=0; i<n; ++i)
        if (g[i].size() > 0)
            bad = true;
    
	if (bad)
		puts ("-1");
	else
		for (size_t i=0; i<res.size(); ++i)
			printf ("%d ", res[i]+1);
    
}
