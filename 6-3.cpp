#include<iostream>
#include<cstring>
#include<queue>
#define INF 1e7
#define N 10
using namespace std;

struct node
{
    int cl;
    int id;
    int x[N];
    node() {}
    node(int c,int i)
    {
        cl=c;
        id=i;
        memset(x,0,sizeof(x));
    }
};

int m[N][N];
int bestx[N];
int bestl;
int n,M;

void init()
{
    int i,j;
    for(i=0; i<N; ++i)
        for(j=0; j<N; ++j)
            m[i][j]=INF;
    memset(bestx,0,sizeof(bestx));
    bestl=INF;
}

struct cmp
{
    bool operator() (node n1,node n2)
    {
        return n1.cl>n2.cl;
    }
};

void bfs()
{
    priority_queue<node,vector<node>,cmp> q;
    node temp(0,2);
    int t;
    for(int i=1; i<=n; ++i)
        temp.x[i]=i;
    q.push(temp);
    node live;
    while(!q.empty())
    {
        live=q.top();
        q.pop();
        t=live.id;
        if(t==n)
        {
            if(m[live.x[t-1]][live.x[t]]!=INF&&m[live.x[t]][1]!=INF)
            {
                if(live.cl+m[live.x[t-1]][live.x[t]]+m[live.x[t]][1]<bestl)
                {
                    bestl=live.cl+m[live.x[t-1]][live.x[t]]+m[live.x[t]][1];
                    for(int i=1; i<=n; ++i)
                        bestx[i]=live.x[i];
                }
            }
            continue;
        }

        if(live.cl>=bestl)
            continue;

        for(int j=t; j<=n; ++j)
        {
            if(m[live.x[t-1]][live.x[j]]!=INF&&live.cl+m[live.x[t-1]][live.x[j]]<bestl)
            {
                temp=node(live.cl+m[live.x[t-1]][live.x[j]],t+1);
                for(int k=1; k<=n; ++k)
                    temp.x[k]=live.x[k];
                swap(temp.x[t],temp.x[j]);
                q.push(temp);
            }
        }
    }
}

void output()
{
    cout<<"The shotest path length is:"<<bestl<<endl;
    cout<<"The route is:";
    for(int i=1; i<=n; ++i)
        cout<<bestx[i]<<"-->";
    cout<<bestx[1]<<endl;
}

int main()
{
    init();
    cin>>n;
    cin>>M;
    int i,a,b,c;
    for(i=0; i<M; ++i)
    {
        cin>>a>>b>>c;
        if(c<m[a][b])
        {
            m[a][b]=c;
            m[b][a]=c;
        }
    }
    bfs();
    output();
    return 0;
}
