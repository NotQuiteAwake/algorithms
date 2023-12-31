#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 1000;
int tree[MAXN], n;

int lowbit(int x){
    return x & (-x);
}
int getsum(int x){
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i)) ans += tree[i];
    return ans;
}
void update(int x, int pos){
    for (int i = pos; i <= n; i += lowbit(i)) tree[i] += x;
}

int main(){
    /*Add your modification here. Size: n.*/
}
