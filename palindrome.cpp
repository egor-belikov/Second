#include <iostream>
#include <algorithm>
#include <string>
#include <set>

const int N = 1000;
std::string d[N][N], s;
std::set < int > l[26];

int main()
{
	std::cin >> s;
	for (int i = 0; i < s.length(); ++i)
		l[s[i]-'A'].insert(i);
	for (int j = 0; j < s.length(); ++j)
		for (int i = 0; i+j < s.length(); ++i)
		{
			int a = i, b = i+j;
			if (a == b)
				d[a][b] = s[a];
			else
			{
				auto f = l[s[b]-'A'].lower_bound(a);
				if (f == l[s[b]-'A'].end() || *f >= b)
					d[a][b] = d[a][b-1];
				else
				{
					std::string nw = s[b] + d[*f+1][b-1] + s[b];
					if (nw.length() > d[a][b-1].length())
						d[a][b] = nw;
					else
						d[a][b] = d[a][b-1];
				}
			}
		}
	std::cout << d[0][s.length()-1].length() << "\n" << d[0][s.length()-1] << "\n";
	return 0;
}