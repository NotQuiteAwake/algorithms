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

using namespace std;

const int MAXN = 505, inf = (int)1e9;

queue<int> q;
int d[MAXN], pre[MAXN], c[MAXN][MAXN], s, t, f[MAXN][MAXN], ans, n, m;
//c: capacity; f: flow;

bool bfs(int s, int t){
    memset(d, 0, sizeof d);
    q.push(s); d[s] = 0;
    while (!q.empty()){
        int cur = q.front(); q.pop();
        for (int v = 0; v <= n; v++){
            if (c[cur][v] > f[cur][v] && !d[v]){
                d[v] = d[cur] + 1; pre[v] = cur; q.push(v);
            }
        }
    }
    return d[t] > 0;
}

int augment(){
    int adj = inf;
    for (int u = t; u != s; u = pre[u]){
        int v = pre[u];
        adj = min(adj, c[v][u] - f[v][u]);
    }
    
    for (int u = t; u != s; u = pre[u]){
        int v = pre[u];
        f[v][u] += adj;
        f[u][v] -= adj;
    }
    return adj;
}

int main(){
    cout << "Please input s(flow start), t(flow end), number of points(n) and number of edges(m):" << endl;
    cin >> s >> t >> n >> m;
    cout << "Please input the network capacity in u, v, w order:" << endl;
    for (int i = 1; i <= m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        c[u][v] = w;
    }
    while (bfs(s, t)){
        ans += augment();
    }
    return 0;
}
