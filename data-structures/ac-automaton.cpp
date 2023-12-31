//AC Automaton
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

const int MAXN = 500010;
queue<int> q;

struct acAuto{
    int c[MAXN][26], val[MAXN], fail[MAXN], cnt, now = 0;
    void ins(string &s){
        int len = (int)s.size();
        for (int i = 0; i < len; i++){
            int v = s[i] - 'a';
            if (!c[now][v]) c[now][v] = ++cnt;
            now = c[now][v];
        }
        val[now]++;
    }
    void build(){
        for (int i = 0; i < 26; i++) if (c[0][i]) fail[c[0][i]] = 0, q.push(c[0][i]);
        while (!q.empty()){
            int u = q.front(); q.pop();
            for (int i = 0; i < 26; i++){
                if (c[u][i]) fail[c[u][i]] = c[fail[u]][i], q.push(c[u][i]);
                else c[u][i] = c[fail[u]][i];
            }
        }
    }
    
    int query(string &s){
        int len = (int)s.size(); int now = 0, ans = 0;
        for (int i = 0; i < len; i++){
            now = c[now][s[i] - 'a'];
            for(int t = now; t && ~val[t]; t = fail[t]) ans += val[t], val[t]=-1;
        }
        return ans;
    }
};
