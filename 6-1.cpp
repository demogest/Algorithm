#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>   
using namespace std;

ifstream fin("matrix1.txt");

class Graph{
	friend int main();
public:
	void ShortesPaths(int);
private:
	int n,*prev;     
	int **c,*dist;     
};

class MinHeapNode
{
	friend Graph;
public:
	operator int()const{ return length; }
	friend bool operator > (const  MinHeapNode &n1, const  MinHeapNode &n2){
		return n1.length>n2.length;
	}
private:
	int i;       
	int length;   
};

void Graph::ShortesPaths(int v){
	priority_queue<MinHeapNode, vector<MinHeapNode>, greater<MinHeapNode> > H;
	MinHeapNode E;	
	E.i = v;
	E.length = 0;
	dist[v] = 0;
	H.push(E);
	while (true){
		try{
			E = H.top();
			H.pop();
		}
		catch (int){
			break;
        }
		for (int j = 1; j <= n; j++)
			if ((c[E.i][j] != 0) && (E.length + c[E.i][j]<dist[j])){			
			    dist[j] = E.length + c[E.i][j];
			    prev[j] = E.i;			
			    MinHeapNode N;
			    N.i = j;
			    N.length = dist[j];
			    H.push(N); 
		    }
		if (H.empty())
			break;
	}
}

int main(){
	int n = 11;
	int prev[12] = {0};
	int dist[12] = {1000};
	cout << "The adjacency matrix of the single source graph is as follows：" << endl;
	int **c = new int*[n + 1];
	for (int i = 1; i <= n; i++)
	{
		c[i] = new int[n + 1];
		for (int j = 1; j <= n; j++)
		{
			fin >> c[i][j];
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	Graph G;
	G.n = n;
	G.c = c;
	G.dist = dist;
	G.prev = prev;
	G.ShortesPaths(1);
	cout << "The shortest path length from S to T is:" << dist[11] << endl;	
    cout<<"The route is:";
    string s="";
    int i=11;
    while (i>1){
        s="->"+to_string(i)+s;
        i=prev[i];
    }
    cout<<"1->"+s<<endl;
	for (int i = 2; i <= n; i++)
		cout << "The shortest path length from 1 to " << i << "is:" << dist[i] << endl;
	for (int i = 1; i <= n; i++)
		delete[]c[i];
	delete[]c;
	c = 0;
	return 0;
}
