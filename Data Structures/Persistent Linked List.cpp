//example: URAL 1992, CVS
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

const int MAXN = 500000 + 10;
int tot = 0, t, m, n, x, y;
string op;

struct ptr{
    int val;
    ptr *pre;
} M[MAXN * 2];

struct Node{
    ptr *a, *b;
} c[MAXN];

inline void add(ptr* &pre, int val){
    ptr *tmp = &M[++tot];
    tmp -> val = val;
    tmp -> pre = pre;
    pre = tmp;
}

void remove(ptr* &last){
    last = last -> pre;
}

int main(){
    cin.sync_with_stdio(false); cout.sync_with_stdio(false);
    tot = 1; n = 1;
    cin >> t >> m;
    for (int i = 0; i < t; i++){
        cin >> op >> x;
        if (op[0] == 'l'){
            cin >> y; add(c[x].a, y); c[x].b = NULL;
        }
        else if (op[0] == 'c' && op[1] == 'l'){
            c[++n] = c[x];
        }
        else if (op[0] == 'r' && op[1] == 'e' && c[x].b != NULL){
            add(c[x].a, c[x].b -> val); remove(c[x].b);
        }
        else if (op[0] == 'r' && op[1] == 'o' && c[x].a != NULL){
            add(c[x].b, c[x].a -> val); remove(c[x].a);
        }
        else {
            if (c[x].a == NULL)cout << "basic" << endl;
            else cout << c[x].a -> val << endl;
        }
    }
    return 0;
}
