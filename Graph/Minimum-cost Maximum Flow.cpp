/*
 Build passed.
 It theoretically works,
 However, it is not yet tested.
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 505, inf = (int)1e9;
queue<int> q;
int d[MAXN], s, n, t, pre[MAXN], r[MAXN][MAXN], ans;
bool vis[MAXN];

struct Edge{
    int u, v, w;
    Edge(int _u, int _v, int _w){
        u = _u; v = _v; w = _w;
    }
};
vector<Edge> g[MAXN];

void connect(int u, int v, int w){
    g[u].push_back(Edge(u, v, w));
}

bool bfs(){
    //optimized Bellman-Ford
    q.push(s); for (int i = 1; i <= n; i++) d[i] = inf;
    d[s] = 0;
    while (!q.empty()){
        int u = q.front(); q.pop(); vis[u] = false;
        for (int i = 0; i < g[u].size(); i++){
            int v = g[u][i].v, w = g[u][i].w;
            if (r[u][v] > 0 && d[v] > d[u] + w){
                pre[v] = u;
                if (!vis[v]) {q.push(v); vis[v] = true;}
                d[v] = d[u] + w;
            }
        }
    }
    return d[t] > 0;
}

int augment(){
    int delta = inf;
    for (int u = t; u != s; u = pre[u]){
        int v = pre[u];
        delta = min(delta, r[v][u]);
    }
    for (int u = t; u != s; u = pre[u]){
        int v = pre[u];
        r[v][u] += delta;
        r[u][v] -= delta;
    }
    return delta;
}

int main(){
    /*Add connection and input remaining network here*/
    while (bfs()) ans += augment();
    return 0;
}
