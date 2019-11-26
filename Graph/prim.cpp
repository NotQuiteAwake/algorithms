#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
	int v, w;
	Edge(int _v, int _w) { v = _v; w = _w; }
};	

int n, m, wt;
const int MAXN = 1000 + 100;
vector<Edge> ve[MAXN];
struct cmp {
	bool operator()(Edge e1, Edge e2) {
		return e1.w > e2.w;	
	}
};

priority_queue<Edge, vector<Edge>, cmp> pq;
bool vis[MAXN];

void add(int _u, int _v, int _w) {
	ve[_u].push_back(Edge(_v, _w));
	ve[_v].push_back(Edge(_u, _w));
}

int main() {
	wt = 0;
	cin >> n >> m;
	int _u, _v, _w;
	for (int i = 1; i <= m; i++) {
		cin >> _u >> _v >> _w;
		add(_u, _v, _w);
	}
	pq.push(Edge(1, 0));
	while (!pq.empty()) {
		Edge e = pq.top(); pq.pop();
	   	int x = e.v;
		if (vis[x]) continue;
		wt += e.w;
		vis[x] = true;
		for (int i = 0; i < ve[x].size(); i++) {
			int v = ve[x][i].v, w = ve[x][i].w;
			if (!vis[v]) pq.push(Edge(v, w));
		}
	}
	cout << wt << endl;
	return 0;
}
