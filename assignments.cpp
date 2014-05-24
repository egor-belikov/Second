#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
using namespace std;


const int inf = INT_MAX;

vector<pair<int, int> > assignments(const vector<vector<int> > &a)
{
    int h = (int)a.size(), w = (int)a[0].size();
    vector<int> u(h, 0), v(w, 0);
    vector<int> mark(w, -1);
    for(int i = 0; i < h; i++)
    {
        vector<int> links(w, -1), mins(w, inf), used(w, 0);
        int marki = i, markj = -1, j;
        while (marki != -1)
        {
            j = -1;
            for (int j1 = 0; j1 < w; j1++)
                if (!used[j1])
                {
                    if (a[marki][j1] - u[marki] - v[j1] < mins[j1])
                    {
                        mins[j1] = a[marki][j1] - u[marki] - v[j1];
                        links[j1] = markj;
                    }
                    if(j == -1 || mins[j1] < mins[j])
                        j = j1;
                }
            int delta = mins[j];
            for (int j1 = 0; j1 < w; j1++)
                if (used[j1])
                {
                    u[mark[j1]] += delta;
                    v[j1] -= delta;
                }
                else
                    mins[j1] -= delta;
            u[i] += delta;
            used[j] = 1;
            markj = j;
            marki = mark[j];
        }
        for(; links[j] != -1; j = links[j])
            mark[j] = mark[links[j]];
        mark[j] = i;
    }
    vector<pair<int, int> > result;
    for (int j = 0; j < w; j++)
        if (mark[j] != -1)
            result.push_back(pair<int, int> (mark[j], j));
    return result;
}

void test()
{
    vector<vector<int> > a;
    vector<int> t;
    for (int i = 0; i < 5; i++)
    {
        a.push_back(t);
        for (int j = 0; j < 5; j++)
        {
            a[i].push_back(rand() % 10);
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    vector<pair<int, int> > res = assignments(a);
    for (int i = 0; i < res.size(); i++)
        cout << res[i].first << " " << res[i].second << endl;
}

int main()
{
    test();
}
