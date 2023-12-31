#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

const int MAXN = 1000 + 100;
vector<int> ve[MAXN];
int n, m, ind[MAXN], cnt, low[MAXN], s[MAXN], stack_size = 0;
bool instack[MAXN], vis[MAXN];

void add(int u, int v){ ve[u].push_back(v); }

void tarjan(int x) {
	ind[x] = low[x] = ++cnt;
	vis[x] = true;
	s[++stack_size] = x; instack[x] = true;
	for (int i = 0; i < ve[x].size(); i++) {
		int v = ve[x][i];
		if (!vis[v]){ tarjan(v); low[x] = min(low[x], low[v]); } //The core of the code - read carefully the conditions and the values.
		else if (instack[v]) low[x] = min(low[x], ind[v]);
	}
	if (low[x] == ind[x]) {
		while (s[stack_size] != x){
			int v = s[stack_size];
			cout << v << " ";
			instack[v] = false;
			stack_size--;
		} 
		cout << x << endl;
		stack_size--;
	}
}

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) { int _u, _v; cin >> _u >> _v; add(_u, _v); }
	for (int i = 1; i <= n; i++) {
		if (vis[i]) continue;
		tarjan(i);	
	}		
}
