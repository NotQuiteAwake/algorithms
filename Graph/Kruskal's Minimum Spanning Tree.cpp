#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 5000, inf = (int)1e9;
int n, m;

struct UnionFind_Set{
    int p[MAXN];
    inline void init(int s){for (int i = 0; i <= s; i++) p[i] = i;}
    int root(int a){p[a] = p[p[a]]; return p[a] == a ? a : root(p[a]);}
    inline void unite(int a, int b){p[root(b)] = root(a);}
    inline bool query(int a, int b){return root(a) == root(b);}
} ufs;
struct Edge{
    int u, v, w;
    Edge(int _u, int _v, int _w){u = _u; v = _v; w = _w;}
    Edge(){u = inf; v = inf; w = inf;}
} e[MAXN];
vector<Edge> graph[MAXN];

void connect(int u, int v, int w){
    graph[u].push_back(Edge(u, v, w));
}
bool cmp(Edge e1, Edge e2){
    return e1.w < e2.w;
}
void kruskal(){
    ufs.init(n);
    sort(e, e + m, cmp);
    for (int i = 0; i < m; i++){
        if (!ufs.query(e[i].u, e[i].v)){
            ufs.unite(e[i].u, e[i].v);
            connect(e[i].u, e[i].v, e[i].w);
            cout << e[i].u << " -> " << e[i].v << ": selected" << endl;
        }
    }
}

int main(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) cin >> e[i].u >> e[i].v >> e[i].w;
    kruskal();
    return 0;
}
