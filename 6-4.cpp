#include <iostream>
#include <string>
#include <queue>
using namespace std;

class BBNode{
	public:
		BBNode *parent;		
		bool isLeftChild;		
};


class MaxHeapQNode{
	public:
		BBNode *liveNode;		
		int upperLimitWeight;		
		int level;		
}; 


struct compare{
	bool operator()(MaxHeapQNode *&a,MaxHeapQNode *&b) const{
		return a->upperLimitWeight < b->upperLimitWeight;
	}
};


void AddLiveNode(priority_queue<MaxHeapQNode*,vector<MaxHeapQNode*>,compare> &q,BBNode *parent,bool isLeft,int upLimit,int level){
	BBNode *b=new BBNode;		
	b->parent = parent;
	b->isLeftChild = isLeft;
	MaxHeapQNode *h = new MaxHeapQNode;		
	h->liveNode=b;
	h->upperLimitWeight=upLimit;
	h->level=level;
	q.push(h);		
}


int MaxLoading(int n,int c,int* w,int* &bestx){
	priority_queue<MaxHeapQNode *,vector<MaxHeapQNode* >,compare> heap;
	int i=0;		
	int ew=0;		
	int nodePriority=0;		
	MaxHeapQNode *h;
	BBNode *e;
	int* remains;		
	remains=new int[n];
	remains[n-1]=0;
	for(int j=n-2;j>=0;j--){	
		remains[j]=remains[j+1]+w[j+1];
	}
	while(i!=n){	
		if(ew+w[i] <= c){		
			nodePriority = ew+w[i]+remains[i];
			AddLiveNode(heap,e,true,nodePriority,i+1);		
		}
		nodePriority=ew+remains[i];
		AddLiveNode(heap,e,false,nodePriority,i+1);		
		h = heap.top();		
		heap.pop();		
		i=h->level;
		e=h->liveNode;	
		ew=h->upperLimitWeight - remains[i-1];		
	}
	
	
	for(int j=n-1;j>=0;j--){
		bestx[j]=e->isLeftChild? 1:0;
		e=e->parent;
	}
	return ew; 		
}

int main(){
	int itemNum;			
	int shipNum;			
	int bestw;  			
	int sumC=0;				
	int sumS=0;				
	cin>>itemNum;
	cin>>shipNum;
	
	int *weight; 	
	weight = new int[itemNum];
	int *bestx; 	
	bestx = new int[itemNum];
	int *ship;		
	ship = new int[shipNum];
	for(int i=0;i<itemNum;i++)
		cin>>weight[i];
	for(int i=0;i<shipNum;i++)
        cin>>ship[i];	
	for(int i=0;i<itemNum;i++)
		sumC=sumC+weight[i];	
	for(int i=0;i<shipNum;i++)
		sumS=sumS+ship[i];	
	int maxC;
	maxC=weight[0];
	for(int i=1;i<itemNum;i++)
		if(maxC<weight[i])
			maxC=weight[i];
	int maxS;
	maxS=ship[0];
	for(int i=i;i<shipNum;i++)
		if(maxS<ship[i])
			maxS=ship[i];	
	if(maxC>maxS || sumC>sumS){
		cout<<"out of capacity, cant load";
		return 0;
	}
	int shipI=0;	
	int cargoI=itemNum;	
	int count=0;	
	while(shipNum!=0){
		bestw=MaxLoading(cargoI,ship[shipI],weight,bestx);		
		int *temp; 	
		temp = new int[itemNum];
		int j=0;
		cout<<"The "+to_string(shipI)+" best loaded weight is:"+to_string(bestw)+"\n";
		cout<<"The item loaded:";
		for(int i=0;i<itemNum;i++){
			if(bestx[i]){
			printf("%d ",weight[i]);
			count++;
			}else{
				temp[j]=weight[i];	
				j++;
			}
	 	}
	 	if(shipNum!=1){
	 		cout<<"\nThe item to be loaded:";
	 		for(int i=0;i<itemNum-count;i++)
	 			cout<<to_string(temp[i])+" ";
		}
		cout<<endl;
	 	for(int i=0;i<itemNum;i++){	
	 		weight[i]=0;
	 		bestx[i]=0;
		 }
		 for(int i=0;i<itemNum-count;i++ ){
		 	weight[i]=temp[i];
		 }
	 	bestw=0;
	 	cargoI=itemNum-count;
	 	shipNum--;
	 	shipI++;
	}
	return 0; 
}