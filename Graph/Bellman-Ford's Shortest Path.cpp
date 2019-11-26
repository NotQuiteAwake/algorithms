#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 1000, inf = (int)1e8 + 234124;
int n, m, s, dist[1000];
queue<int> q;
bool vis[MAXN];

struct Edge {
	int u, v, w;
	Edge(int _u, int _v, int _w) {
		u = _u, v = _v, w = _w;
	}
};
vector<Edge> graph[MAXN];

inline void connect(int u, int v, int w) {
	graph[u].push_back(Edge(u, v, w));
}

inline void init(int s) {
	for (int i = 0; i < MAXN; i++) dist[i] = inf, vis[i] = false; dist[s] = 0; vis[s] = true;
}

void bellman_ford(int s) {
	init(s);
	int cur;
	q.push(s);
	while (!q.empty()) {
		cur = q.front(); vis[cur] = false; q.pop();
		for (int i = 0; i < graph[cur].size(); i++) {
			if (dist[graph[cur][i].v] > dist[cur] + graph[cur][i].w) {
				dist[graph[cur][i].v] = dist[cur] + graph[cur][i].w;
				if (!vis[graph[cur][i].v]) q.push(graph[cur][i].v);
				vis[graph[cur][i].v] = true;
			}
		}
	}
}

int main() {
	cout << "Please input n(number of points), m(number of edges) and s(starting point):" << endl;
	cin >> n >> m >> s;
	cout << "Please input u, v and w:" << endl;
	for (int i = 1; i <= m; i++) {
		int __u, __v, __w;
		cin >> __u >> __v >> __w;
		connect(__u, __v, __w);
	}
	bellman_ford(s);
	for (int i = 1; i <= n; i++) {
		cout << dist[i] << " ";
	}
	cout << endl;
	return 0;
}
