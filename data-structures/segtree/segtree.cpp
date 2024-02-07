// segment tree.
//
// could also have generated leaf nodes when in need only, assigning some kind
// of ++n to the ptr of the newly generated leaf node.
// however if there are many operations then they end up being the same.
//
// space also has to be pre-allocated anyway.

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000;  // max range
int range; // range of interval (start from 1)
int u;  // number of update instructions
int q;  // number of query instructions

struct segTreeNode {
    int val;    // sum on this node / interval
    int mark;   // lazy mark
} segTree[MAXN * 4 + 50];

void pushDown(int ptr, int l, int r) {
    int &cmark = segTree[ptr].mark;
    int mid = (l + r) / 2;

    segTreeNode &lchild = segTree[ptr * 2];
    segTreeNode &rchild = segTree[ptr * 2 + 1];

    lchild.mark += cmark;
    rchild.mark += cmark;

    lchild.val += cmark * (mid - l + 1);
    rchild.val += cmark * (r - (mid + 1) + 1);

    cmark = 0;
}

void update(int ptr, int reql, int reqr, int l, int r, int delta) {
    int &cval = segTree[ptr].val;
    int &cmark = segTree[ptr].mark;
    int mid = (l + r) / 2;

    // falls outside required range
    if (r < reql || l > reqr) return;

    // fully in range - use lazy mark
    if (reql <= l && r <= reqr) {
        cval += delta * (r - l + 1);
        cmark += delta;
        return;
    }

    // otherwise partially in range
    // propagate lazy mark along the way
    if (cmark != 0) pushDown(ptr, l, r);

    update(ptr * 2, reql, reqr, l, mid, delta);
    update(ptr * 2 + 1, reql, reqr, mid + 1, r, delta);

    // this is why cmarks must be pushDown-ed
    // if not some lazily added sum on cval is lost
    cval = segTree[ptr * 2].val + segTree[ptr * 2 + 1].val;

//    cout << l << " " << r << " " << cval << endl;
}

int query(int ptr, int reql, int reqr, int l, int r) {
    int &cval = segTree[ptr].val;
    int mid = (l + r) / 2;

//    cout << l << " " << r << " " << cval << endl;

    if (r < reql || l > reqr) return 0;

    if (reql <= l && r <= reqr) {
        return segTree[ptr].val;
    }

    // else, partially in range
    // subregions need to know the extra lazy add that applies
    // as that is not reflected in their stored sum yet
    pushDown(ptr, l, r);

    return query(ptr * 2, reql, reqr, l, mid) +
           query(ptr * 2 + 1, reql, reqr, mid + 1, r);
}


int main() {
    cin >> u >> q >> range;
    for (int i = 1; i <= u; i++) {
        int l, r, delta;
        cin >> l >> r >> delta;
        update(1, l, r, 1, range, delta);
//        cout << query(1, l, r, 1, range) << endl;
    }
    for (int i = 1; i <= q; i++) {
        int l, r;
        cin >> l >> r;
        cout << query(1, l, r, 1, range) << endl;
    }
    return 0;
}
