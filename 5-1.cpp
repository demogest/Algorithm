#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;

const int N = 1010;
const int V = 1010;
int pri[N], wet[N];
int n, w;
int m[N][N];
int dfs(int a, int b) {
    if (m[a][b] != -1)return m[a][b];
    if (a == n + 1 || b == 0)return 0;
    int t1 = 0, t2 = 0;
    if (b >= wet[a]) t1 = dfs(a + 1, b - wet[a]) + pri[a];
    t2 = dfs(a + 1, b);
    m[a][b] = max(t1, t2);;
    return max(t1, t2);
}
int main() {
    cin >> n >> w;
    if (n <= 0 || w <= 0) {
        cout << 0; return 0;
    }
    for (int i = 1; i <= n; i++) {
        cin >> pri[i] >> wet[i];
    }
    memset(m, -1, sizeof(m));
    int res = dfs(1, w);
    cout << res << endl;
    return 0;
}