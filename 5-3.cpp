#include<cstdio>
using namespace std;
const int num=110;
int n,m,cn,rn,bn;
int e[num][num];
int x[num],bx[num];
void BackTrack(int i) 
{
    if(i>n){
        if(cn>bn){            
            for(int i=1;i<=n;i++) bx[i]=x[i];
            bn=cn;
        }
        return ;
    }
    rn=n-i;    
    if(cn+1+rn>bn){
        int f=1;
        for(int k=1;k<=n;k++) 
        {
            if(x[k]&&e[i][k]==0){
                f=0;break;
            }
        }
        if(f){
            cn++;
            x[i]=1;
            BackTrack(i+1);
            
            x[i]=0;
            cn--;
        }
    } 
    if(cn+rn>bn){
        x[i]=0;
        BackTrack(i+1);
    }

}
int main()
{
    
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) e[i][i]=1;
    int u,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        e[u][v]=e[v][u]=1;
    } 
    BackTrack(1);
    printf("Bn:%d\n",bn);
    for(int i=1;i<=n;i++) 
    if(bx[i]) printf("%d ",i);

    return 0;
}
/*
样例：
5 7
1 2
2 3
3 5
4 5
1 4
1 5
2 5
*/