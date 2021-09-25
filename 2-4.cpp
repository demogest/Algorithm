#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e2 + 5;
int num, val, n;
int a[maxn];
void find(int &l, int &r, int id)
{
    l = r = id;
    while (a[l] == a[id] && l >= 0)
        --l;
    while (a[r] == a[id] && r < n)
        ++r;
    l++,r--;
    return;
}
void solve(int l, int r)
{
    if (l > r)
        return;
    int mid = l + r >> 1;
    int i, j;
    find(i, j, mid);
    if (j - i + 1 > num)
    {
        num = j - i + 1;
        val = a[mid];
    }
    if (i - l > num)
        solve(l, i - 1);
    if (r - j > num)
        solve(j + 1, r);
    return;
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a + n);
    for (int i = 0; i < n; ++i)
        cout<<a[i]<<(i == n-1 ? '\n':' ');
    num = val = 0;
    solve(0, n - 1);
    printf("%d %d\n", val, num);
    return 0;
}
