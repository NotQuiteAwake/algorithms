#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
int u, q, tmp;

struct segTreeNode {
	int val, mark;
} segTree[MAXN * 4 + 10];

void pushDown(int ptr, int l, int r) {
	int &cmark = segTree[ptr].mark, mid = (l + r) / 2;
	segTree[ptr * 2].mark += cmark; segTree[ptr * 2 + 1].mark += cmark;
	segTree[ptr * 2].val += cmark * (mid - l + 1); segTree[ptr * 2 + 1].val += cmark * (r - mid);
	cmark = 0;
}

void update(int ptr, int reql, int reqr, int l, int r, int val) {
	int &cval = segTree[ptr].val, &cmark = segTree[ptr].mark, mid = (l + r) / 2;
	if (r < reql || l > reqr) return;
	if (reql <= l && r <= reqr) { cval += val * (r - l + 1);  cmark += val; return; }
	if (cmark != 0) pushDown(ptr, l, r);
	update(ptr * 2, reql, reqr, l, mid, val);
	update(ptr * 2 + 1, reql, reqr, mid + 1, r, val);
	cval = segTree[ptr * 2].val + segTree[ptr * 2 + 1].val;
}

int query(int ptr, int reql, int reqr, int l, int r) {
	int &cval = segTree[ptr].val, mid = (l + r) / 2;
	if (r < reql || l > reqr) return 0;
	if (reql <= l && r <= reqr) { return segTree[ptr].val; }
	pushDown(ptr, l, r);
	return query(ptr * 2, reql, reqr, l, mid) + query(ptr * 2 + 1, reql, reqr, mid + 1, r);
}


int main() {
	cin >> u >> q;
	for (int i = 1; i <= u; i++) {
		int l, r;
		cin >> l >> r >> tmp;
		update(1, l, r, 1, MAXN, tmp);
	}
	for (int i = 1; i <= q; i++) {
		int l, r;
		cin >> l >> r;
		cout << query(1, l, r, 1, MAXN) << endl;
	}
	return 0;
}