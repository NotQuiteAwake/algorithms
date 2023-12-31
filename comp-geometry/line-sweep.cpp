#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 205;
double y[maxn << 1];

struct segTreeNode{
    double l, r, x;
    int cover;
    bool flag;
    segTreeNode(){flag = false; l = r = x = cover = 0;}
    segTreeNode(double _l, double _r, double _x, bool _flag, int _cover){
        flag = _flag; l = _l; r = _r; x = _x; cover = _cover;
    }
} segTree[maxn << 2];

void build(int ptr, int l, int r){
    int mid = (l + r) >> 1;
    segTree[ptr] = segTreeNode(y[l], y[r], -1, (l + 1 == r), 0);
    if (l + 1 != r) build(ptr << 1, l, mid), build(ptr << 1 | 1, mid, r);
}

inline void update(int ptr, int delta, double x){
    segTree[ptr].cover += delta; segTree[ptr].x = x;
}

double update_query(int ptr, double l, double r, double x, int delta){
    if (segTree[ptr].r <= l || r <= segTree[ptr].l) return 0;
    if (segTree[ptr].flag){
        double ans = (x - segTree[ptr].x) * (segTree[ptr].r - segTree[ptr].l) * (segTree[ptr].cover > 0);
        update(ptr, delta, x);
        return ans;
    }
    return update_query(ptr << 1, l, r, x, delta) + update_query(ptr << 1 | 1, l, r, x, delta);
}

int n;
double x1, x2, y1, y2;
struct line{
    double x, y_up, y_down;
    int flag;
    line(){}
    line(double x1, double y1, double y2, int _flag){
        x = x1; y_down = y1; y_up = y2; flag = _flag;
    }
} l[maxn];

inline bool cmp(line l1, line l2){
    return l1.x < l2.x;
}

int main(){
    int cs = 0;
    while (~scanf("%d",&n)&&n){
        int cnt = -1;
        double area = 0;
        for (int i = 0; i < n; i++){
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            y[++cnt] = y1;
            l[cnt] = line(x1, y1, y2, 1);
            y[++cnt] = y2;
            l[cnt] = line(x2, y1, y2, -1);
        }
        sort(y, y + cnt + 1);
        sort(l, l + cnt + 1, cmp);
        build(1, 0, cnt);
        for(int i = 0; i <= cnt; i++){
            area += update_query(1, l[i].y_down, l[i].y_up, l[i].x, l[i].flag);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",++cs,area);
    }
    return 0;
}

