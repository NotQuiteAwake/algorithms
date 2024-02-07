#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 1000;
int val[MAXN];

int u, d, range;

void update(int l, int r, int delta) {
    for (int i = l; i <= r; i++) {
        val[i] += delta;
    }
}

int query(int l, int r) {
    int sum = 0;
    for (int i = l; i <= r; i++) {
        sum += val[i];
    }
    return sum;
}

int main() {
    cin >> u >> d >> range;
    for (int i = 0; i < u; i++) {
        int l, r, delta;
        cin >> l >> r >> delta;
        update(l, r, delta);
    }

    for (int i = 0; i < d; i++) {
        int l, r;
        cin >> l >> r;
        cout << query(l, r) << endl;
    }

    return 0;
}

