//Treap
#include <cstring>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxNode = 100000;
struct Treap {
	int root, treapCnt, key[maxNode], prio[maxNode], ch[maxNode][2], cnt[maxNode], size[maxNode];

	inline int random() {
		static int seed = 703;
		return seed = int(seed * 48271LL % 2147483647);
	}

	Treap() {
		treapCnt = 1;
		root = 0;
		prio[0] = random();
		size[0] = 0;
	}

	inline void update(int x) {
		size[x] = cnt[x] + size[ch[x][0]] + size[ch[x][1]];
	}

	inline void rotate(int &x, int t) {
		int y = ch[x][t];
		ch[x][t] = ch[y][1 - t];
		ch[y][1 - t] = x;
		update(x), update(y);
		if (x == root) root = y;
		x = y;
	}

	void __insert(int &x, int k) {
		if (x) {
			if (key[x] == k) cnt[x]++;
			else {
				int t = k > key[x];
				__insert(ch[x][t], k);
				if (prio[ch[x][t]] < prio[x]) rotate(x, t);
			}
		}
		else {
			x = treapCnt++;
			key[x] = k;
			cnt[x] = 1;
			prio[x] = random();
			ch[x][0] = ch[x][1] = 0;
		}
		update(x);
	}

	void __erase(int &x, int k) {
		if (key[x] == k) {
			if (cnt[x] > 1) cnt[x]--;
			else {
				if (ch[x][1] == 0 && ch[x][0] == 0) { x = 0; return; }
			}
			int t = prio[ch[x][0]] > prio[ch[x][1]];
			rotate(x, t);
			__erase(x, t);
		}
		else {
			__erase(ch[x][key[x] < k], k);
		}
		update(x);
	}

	int __getKth(int &x, int k) {
		if (k <= size[x]) return __getKth(ch[x][0], k);
		k -= size[x];
		if (k <= 0) return -1;
		return __getKth(ch[x][1], k);
	}

	inline void insert(int k) { __insert(root, k); }
	inline void erase(int k) { __erase(root, k); }
	inline int getKth(int k) { return __getKth(root, k); }
};
