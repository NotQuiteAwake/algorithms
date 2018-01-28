const int MAXN = 1000;
struct UnionFind_Set {
	int p[MAXN];
	inline void init(int s) { for (int i = 0; i <= s; i++) p[i] = i; }
	int root(int a) { p[a] = p[p[a]]; return p[a] == a ? a : root(p[a]); }
	inline void unite(int a, int b) { p[root(b)] = root(a); }
	inline bool query(int a, int b) { return root(a) == root(b); }
} ufs;