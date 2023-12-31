#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

inline int read() {
	int x = 0, f = 1;
	char ch = getchar(); 
	while (ch < '0' || ch > '9'){if (ch == '-') f = -1; ch = getchar();}	
	while (ch >= '0' && ch <= '9') {x *= 10; x += ch - '0'; ch = getchar();}
	return f * x;	
}

const int MAXN = 1000;
int n, m;
int ve[MAXN][MAXN][2];

int main(){
	memset(ve, 0x3f, sizeof ve);
	for (int i = 1; i <= n; i++) {ve[i][i][0] = 0;}
	ios::sync_with_stdio(false);
	n = read(); m = read();
	for (int i = 1; i <= m; i++) {
		int _u = read(); int _v = read(); int _w = read();
		ve[_u][_v][0] = _w;
		ve[_v][_u][0] = _w;		
	}
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int c = k % 2; int l = c ^ 1;
				ve[i][j][c] = min(ve[i][k][l] + ve[k][j][l], ve[i][j][l]);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			cout << i << " " << j << " " << ve[i][j][n % 2] << endl;
		}
	}
	return 0;
}
