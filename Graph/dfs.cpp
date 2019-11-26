#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 1000 + 100;
vector<int> ve[MAXN];
bool vis[MAXN];
int n, m;

void add(int u, int v) { ve[u].push_back(v); }

void dfs(int x) {
	cout << x << endl;
	vis[x] = true;
	for (int i = 0; i < ve[x].size(); i++) {
		int v = ve[x][i];
		if (!vis[v]) dfs(v);
	}
}

int main() {
	memset(vis, 0, sizeof vis);
	ios::sync_with_stdio(false);
	int _u = 0, _v = 0;
	
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> _u >> _v;
		add(_u, _v);
	}
	dfs(1);	
	return 0;
}
