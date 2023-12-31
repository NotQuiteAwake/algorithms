#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000 + 100;

int n, m;
vector<int> ve[MAXN];
queue<int> q;
bool vis[MAXN];

void add(int u, int v){ ve[u].push_back(v); }

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int _u, _v; cin >> _u >> _v; add(_u, _v);
	}
	q.push(1);
	vis[1] = true;
	while (!q.empty()) {
		int x = q.front(); q.pop();
		cout << x << endl;
		for (int i = 0; i < ve[x].size(); i++) {
			int v = ve[x][i];
			if (vis[v]) continue; 
			q.push(v); vis[v] = true;
		}
	}
	return 0;
}
