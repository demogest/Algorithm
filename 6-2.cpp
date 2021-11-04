#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef int Typew;
typedef int Typep;   
class Object{
	friend Typep Knapsack(Typew *, Typep *, Typew, int, int *);
public:
	int operator <= (Object a) const{
		return (d >= a.d);
	}
private:
	int ID; 
	float d; 
};
class bbnode{
	friend class Knap;
	friend Typep Knapsack(Typew *, Typep *, Typew, int, int *);
private:
	bbnode *parent; 
	int LChild; 
};
class HeapNode{
	friend class Knap;
	friend class MaxHeap;
public:
	operator Typep()const{ return uprofit; };
	friend bool operator > (const  HeapNode &n1, const  HeapNode &n2){
		return n1.uprofit<n2.uprofit;  
	}
private:
	Typep uprofit, 
		profit; 
	Typew weight; 
	int level; 
	bbnode *elemPtr; 
};
class Knap{	
	friend Typep Knapsack(Typew *, Typep *, Typew, int, int *);
public:
	Typep MaxKnapsack();
private:	
	Typep Bound(int i);	
	void AddLiveNode(Typep up, Typep cp, Typew cw, int ch, int level);
	bbnode *E; 
	Typew c; 
	int n; 
	Typew *w; 
	Typep *p; 
	Typew cw; 
	Typep cp; 
	int *bestx; 
	priority_queue<HeapNode, vector<HeapNode>, greater<HeapNode> > H;
};
Typep Knap::MaxKnapsack(){
	bestx = new int[n + 1];
	int i = 1; 
	E = 0; 
	cw = 0;
	cp = 0;
	Typep bestp = 0; 
	Typep up;
	while (i != n + 1)	{		
		Typew wt = cw + w[i]; 
		if (wt <= c){
			if (cp + p[i] > bestp)
				bestp = cp + p[i];
			AddLiveNode(up, cp + p[i], cw + w[i], 1, i);
		}
		up = Bound(i + 1);
		if (up > bestp)
			AddLiveNode(up, cp, cw, 0, i);
		HeapNode N;
		N = H.top(); 
		H.pop();
		E = N.elemPtr;
		cw = N.weight;
		cp = N.profit;
		up = N.uprofit;
		i = N.level + 1; 
	}
	
	for (int j = n; j > 0; j--){
		bestx[j] = E->LChild;
		E = E->parent;
	}
	return cp;
}

Typep Knap::Bound(int i){
	Typew cleft = c - cw;
	Typep b = cp;
	while (i <= n && w[i] <= cleft){
		cleft -= w[i];
		b += p[i];
		i++;
	}
	if (i <= n) b += p[i] / w[i] * cleft;
	return b;
}
void Knap::AddLiveNode(Typep up, Typep cp, Typew cw, int ch, int level){
	bbnode *b = new bbnode;
	b->parent = E; 
	b->LChild = ch;
	HeapNode N;
	N.uprofit = up;
	N.profit = cp;
	N.weight = cw;
	N.level = level;
	N.elemPtr = b;
	H.push(N);
}
Typep Knapsack(Typew *w, Typep *p, Typew c, int n, int *bestx){
	Typew W = 0;
	Typep P = 0;
	Object *Q = new Object[n];
	int i;
	for (i = 1; i <= n; i++){
		Q[i - 1].ID = i;
		Q[i - 1].d = 1.0*p[i] / w[i];
		P += p[i];
		W += w[i];
	}	
	if (W <= c){
		for (int i = 1; i <= n; i++)
			bestx[i] = p[i];
		return P;
	}	
	for (i = 1; i<n; i++)
		for (int j = 1; j <= n - i; j++){
			if (Q[j - 1].d < Q[j].d){
				Object temp = Q[j - 1];
				Q[j - 1] = Q[j];
				Q[j] = temp;
			}
		}
	Knap K;
	K.p = new Typep[n + 1];
	K.w = new Typew[n + 1];
	for (i = 1; i <= n; i++){
		K.p[i] = p[Q[i - 1].ID];
		K.w[i] = w[Q[i - 1].ID];
	}
	K.cp = 0;
	K.cw = 0;
	K.c = c;
	K.n = n;
	Typep bestp = K.MaxKnapsack();
	for (i = 1; i <= n; i++)
		bestx[Q[i - 1].ID] = K.bestx[i];
	delete[] Q;
	delete[] K.w;
	delete[] K.p;
	delete[] K.bestx;
	return bestp;
}
int main(){
	int N,bestp;
	Typew c;
	cin>>N>>c;
	int *bestx = new int [N+1];
	Typep *p = new Typep[N+1];//{ -1, 6, 4, 7, 4 }
	Typew *w = new Typew[N+1];//{ -1, 2, 3, 5, 2 }
	for (int i=1;i<=N;i++)
		cin>>p[i]>>w[i];
	bestp = Knapsack(w, p, c, N, bestx);
	cout << "Total number of items = " << N << ",The capacity of knapsack = " << c << endl;
	int i;
	for (i = 1; i <= N; i++){
		if (i == 1) cout << "Array of weight:";
		cout << w[i];
		if (i != N) cout << ",";
		else
			cout << endl;
	}
	for (i = 1; i <= N; i++){
		if (i == 1) cout << "Array of price:";
		cout << p[i];
		if (i != N) cout << ",";
		else
			cout << endl;
	}
	for (i = 1; i <= N; i++)
	{
		if (i == 1) cout << "Whether to select:";
		cout << bestx[i];
		if (i != N) cout << ",";
		else
			cout << endl;
	}
	cout << "The best price of the knapsack:" << bestp << endl;
	return 0;
}