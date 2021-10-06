#include <bits/stdc++.h>
using namespace std;
int tile=0;
void chessBoard( int tr, int tc, int dr, int dc, int size, vector< vector<int>> &Board){
    if (size==1){
        return;
    }
    int t=++tile;
    int s=size>>1;
    if (dr < tr + s && dc < tc + s){
        chessBoard(tr,tc,dr,dc,s,Board);
    }
    else{
        Board[tr+s-1][tc+s-1]=t;
        chessBoard(tr,tc,tr+s-1,tc+s-1,s,Board);
    }
    if (dr < tr + s && dc >= tc + s){
        chessBoard(tr,tc+s,dr,dc,s,Board);
    }
    else{
        Board[tr+s-1][tc+s]=t;
        chessBoard(tr,tc+s,tr+s-1,tc+s,s,Board);
    }
    if (dr >= tr + s && dc < tc +s){
        chessBoard(tr+s,tc,dr,dc,s,Board);
    }
    else{
        Board[tr+s][tc+s-1]=t;
        chessBoard(tr+s,tc,tr+s,tc+s-1,s,Board);
    }
    if (dr >= tr + s && dc >= tc + s){
        chessBoard(tr+s,tc+s,dr,dc,s,Board);
    }
    else{
        Board[tr+s][tc+s]=t;
        chessBoard(tr+s,tc+s,tr+s,tc+s,s,Board);
    }
}
int main(){
    int n;
    cin>>n;
    vector< vector<int>> Board(n, vector<int>(n, 0));
    int dr,dc;
    cin>>dr>>dc;
    chessBoard(0,0,dr,dc,n,Board);
    for (auto it = Board.begin();it != Board.end();it++){
        for (auto it2 = (*it).begin();it2!=(*it).end();it2++){
            cout<<*it2<<"\t";
        }
        cout<<endl;
    }
    return 0;
}