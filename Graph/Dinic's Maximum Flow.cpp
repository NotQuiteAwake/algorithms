//Possible Runtime Error. Works fine on small data sets.
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 20000 + 100, INF = (int)1e9;
int n, m, a, b, w, edge = 1, s, t, r[500005], cur[MAXN], d[MAXN], id = 0;
long long ans = 0;
queue<int> q;

struct Edge{
    int u, v, w, id, revid;
    Edge(int _u, int _v, int _w, int _id, int _revid){
        u = _u; v = _v; w = _w; id = _id; revid = _revid;
    }
};

vector<Edge> g[MAXN];

void connect(int a, int b, int w){
    g[a].push_back(Edge(a, b, w, id + 1, id + 2));
    g[b].push_back(Edge(b, a, w, id + 2, id + 1));
    r[id + 1] = w; r[id + 2] = w;
    id += 2;
}

long long dfs(int u, int b){
    if (u == t) return b;
    int ans = 0;
    for (int &e = cur[u]; e < n; e++){
        int v = g[u][e].v, cid = g[u][e].id, revid = g[u][e].revid;
        if (d[v] == d[u] + 1 && r[cid] > 0){
            long long w = dfs(v, min(b, r[cid]));
            b -= w; ans += w;
            r[cid] -= w; r[revid] += w;
            if (b == 0) break;
        }
    }
    return ans;
}

bool bfs(){
    memset(d, 0, sizeof d);
    q.push(s); d[s] = 1;
    while (!q.empty()){
        int cur = q.front(); q.pop();
        for (int i = 0; i < g[cur].size(); i++){
            int v = g[cur][i].v, cid = g[cur][i].id;
            if (r[cid] > 0 && !d[v]){
                d[v] = d[cur] + 1; q.push(v);
            }
        }
    }
    return d[t] > 0;
}

int main(){
    cin >> n >> m;
    s = 0; t = n + 1;
    for (int i = 1; i <= n; i++){
        cin >> a >> b;
        connect(s, i, a);
        connect(i, t, b);
    }
    while (m-- > 0){
        cin >> a >> b >> w;
        connect(a, b, w);
    }
    while (bfs()){
        memset(cur, 0, sizeof cur);
        ans += dfs(s, INF);
    }
    cout << ans << endl;
    return 0;
}