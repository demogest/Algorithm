#include <bits/stdc++.h>
using namespace std;
class MachineNode{
    public:
        MachineNode(int id,int avail){
            this->id = id;
            this->avail = avail;
        }
        friend int main();
        operator int () const{
            return avail;
        }
        friend bool operator >(const MachineNode &a,const MachineNode &b){
            return a.avail > b.avail;
        }
    private:
        int id,avail;
};
class JobNode{
    public:
        JobNode(int id,int time){
            this->id = id;
            this->time = time;
        }
        friend int main();
        operator int () const{
            return time;
        }
        friend bool operator > (const JobNode &a,const JobNode &b){
            return a.time > b.time;
        }
    private:
        int id,time;
};

int main(){
    int n,m;
    cin>>n>>m;
    if (n<=m){
        cout<<"将所有任务依次分配给各机器\n";
        return 0;
    }
    vector<JobNode> job;
    for (int i=0;i<n;i++){
        int time;
        cin>>time;
        JobNode a(i+1,time);
        job.push_back(a);
    }    
    sort(job.begin(),job.end(),greater<JobNode>());
    priority_queue<MachineNode,vector<MachineNode>,greater<MachineNode>> q;
    for (int i=0;i<m;i++){
        cout<<"将机器"<<i+1<<"从"<<0<<"到"<<job[i].time<<"分配给作业"<<job[i].id<<endl;
        MachineNode x(i+1,job[i].time);
        q.push(x);
    }
    for (int i=m;i<n;i++){
        MachineNode x = q.top();
        q.pop();
        cout<<"将机器"<<x.id<<"从"<<x.avail<<"到"<<x.avail+job[i].time<<"分配给作业"<<job[i].id<<endl;
        x.avail+=job[i].time;
        q.push(x);
    }
    q.pop();q.pop();
    cout<<"总耗时:"<<(q.top()).avail;
}