#include <bits/stdc++.h>
using namespace std;
void Exec(vector<int> a,int l,int r){
    if ( l == r){
        for (int i=0;i<=r;i++)
            cout<<a[i]<<((i == r)? "\n":"");
        return;
    }
    for (int i=l;i<=r;i++){
        swap(a[i],a[l]);
        Exec(a,l+1,r);
        swap(a[i],a[l]);
    }
}
/*
int main(){
    vector<int> a;
    int n;
    cin>>n;
    a.resize(n);
    for (int i=0;i<n;i++){
        cin>>a[i];
    }
    Exec(a,0,n-1);
    return 0;
}
*/