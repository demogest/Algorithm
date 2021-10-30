#include<iostream>
#include<algorithm>
#define MAX 100
using  namespace std;
int n;
int a[MAX][MAX];
int x[MAX];
int bestx[MAX]  = {0}; 
int bestp = 63355;
int cp = 0;
void backpack(int t){
     if(t>n){
        if((a[x[n]][1])&&(a[x[n]][1]+cp<bestp)){
              bestp = a[x[n]][1]+cp;
              for(int i = 1;i<=n;i++){
                 bestx[i] = x[i];
              }
        }
     }else{
         for(int i = t;i<=n;i++){
            if((a[x[t-1]][x[i]])&&(cp+a[x[t-1]][x[i]]<bestp)){
                swap(x[t],x[i]);   
                cp+=a[x[t-1]][x[t]];
                backpack(t+1);
                cp-=a[x[t-1]][x[t]];
                swap(x[t],x[i]);
            }
         }
    }
}
int main(){
    cout<<"输入城市个数:"<<endl;
    cin>>n;
    for(int i = 1;i<=n;i++){
         x[i] = i;
    }
    cout<<"输入城市之间的距离(0表示城市间不通):"<<endl;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    backpack(2);
    cout<<"最少旅行费用为: "<<bestp<<endl;
    cout<<"旅行路径为:"<<endl;
    for(int i = 1;i<=n;i++){
       cout<<bestx[i]<<" ";
    }
    cout<<bestx[1];
    return 0;
}
/*
input:
4
0 30 6 4
30 0 5 10
6 5 0 20
4 10 20 0
*/
