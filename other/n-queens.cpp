//N Queen Problem - DFS method
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 1000;
int stat[MAXN], cnt, n;

bool check(int r, int c){
    for (int i = 1; i < r; i++){
        if (stat[i] == c || stat[i] + (r - i) == c || stat[i] - (r - i) == c) return false;
    }
    return true;
}

void print(){
    for (int i = 1; i <= n; i++) cout << i << ": " << stat[i] << endl;
}

void dfs(int r){
    for (int i = 1; i <= n; i++){
        if (cnt == 0) return;
        if (check(r, i)){
            stat[r] = i;
            if (r == n) { print(); cnt--; return; }
            else dfs(r + 1);
        }
    }
}

int main(){
    cin >> n >> cnt;
    dfs(1);
    return 0;
}
