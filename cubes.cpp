#include <vector>
#include <iostream>
#include <string>

using namespace std;
typedef vector<int> veint;
typedef vector<veint> lists;

bool try_kuhn (veint &used, const lists &g, veint &mt, const int v) {//находим максимальное паросочетание алгоритмом Куна
	if (used[v])
        return false;
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn (used, g, mt, mt[to])) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}

int main() {
	int n;
    cin >> n; //количество кубиков
    string word;
    cin >> word; //слово, которое мы собираем
    vector<string> cubes;
    for (int i = 0; i < n; i++)
    {
        string temp;
        cin >> temp; //буквы, из которых состоят кубики, нужно указывать без пробелов
        cubes.push_back(temp);
    }
    int k = (int) word.length();
    lists g;
    veint mt;
    veint used;
    for (int i = 0; i < n; i++)
    {
        veint empty;
        g.push_back(empty);
        for (int j = 0; j < cubes[i].length(); j++)
            for (int k = 0; k < word.length(); k++)
                if (cubes[i][j] == word[k])
                    g[i].push_back(k);
    }
	mt.assign (k, -1);
	for (int v=0; v<n; ++v) {
		used.assign (n, false);
		try_kuhn (used, g, mt, v);
	}
    for (int i = 0; i < k; i++)
        if (mt[i] == -1)
        {
            cout << "NO\n";
            return 0;
        }
    cout << "YES\n";
    for (int i=0; i<k; ++i)
        cout << mt[i] + 1 << " ";
    cout << endl;
}
