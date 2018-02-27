#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 1000, inf = (int)1e8 + 1231512;
int n, m, dis[MAXN], s;
struct fow{
	int dis, pos; 
	fow(int _dis, int _pos){dis = _dis, pos = _pos;}
};

struct cmp{
	bool operator()(fow f1, fow f2){
		return f1.dis > f2.dis;
	}
};

priority_queue<fow, vector<fow>, cmp> q;

struct Edge{
	int u, v, w;
	Edge(int _u, int _v, int _w){
		u = _u, v = _v, w = _w;
	}
};
vector<Edge> graph[MAXN];

inline void connect(int u, int v, int w){
	graph[u].push_back(Edge(u, v, w));
}

void dijkstra(int s){
	for (int i = 0; i <= n; i++){
		dis[i] = inf;
	}	
	dis[s] = 0;
	fow cur(0, 0);
	q.push(fow(0, s));
	while (!q.empty()){
		cur = q.top(); q.pop();
		for (int i = 0; i < graph[cur.pos].size(); i++){
			int new_dis = graph[cur.pos][i].w + cur.dis, &old_dis = dis[graph[cur.pos][i].v];
			if (old_dis > new_dis){
				old_dis = new_dis;
				q.push(fow(new_dis, graph[cur.pos][i].v));
			}
		}
	}
}

int main(){
	cout << "Please input n(number of points), m(number of edges) and s(starting point):" << endl;
	cin >> n >> m >> s;
	cout << "Please input u, v and w:" << endl;
	for (int i = 1; i <= m; i++){
		int __u, __v, __w;
		cin >> __u >> __v >> __w;
		connect(__u, __v, __w);
	}
	dijkstra(s);
	for (int i = 1; i <= n; i++){
		cout << dis[i] << " ";
	}
	cout << endl;
	return 0;
}
