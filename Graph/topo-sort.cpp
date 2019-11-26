#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000 + 100;
int seq[MAXN], n, m, ind[MAXN], cnt;
vector<int> ve[MAXN];
queue<int> q;

void add(int u, int v) { ve[u].push_back(v); ind[v]++; }

int main() {
	cin >> n >> m;
	int _u, _v;
	for (int i = 1; i <= m; i++) {
		cin >> _u >> _v;
		add(_u, _v);
	}
	for (int i = 1; i <= n; i++) { if (!ind[i]) { q.push(i);  }}
	while (!q.empty())	{
		int x = q.front(); q.pop(); seq[++cnt] = x;
		for (int i = 0; i < ve[x].size(); i++) {
			int v = ve[x][i];
			if (!--ind[v]) { q.push(v); }
		}
	}
	
	for (int i = 1; i <= cnt; i++) { cout << seq[i] << " "; }
	return 0;
}
