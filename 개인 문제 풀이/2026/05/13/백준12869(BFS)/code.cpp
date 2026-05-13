#include <bits/stdc++.h> 
using namespace std;
int a[3];
int visited[62][62][62];
int dd[6][3] = { //데미지 조합
    {9,3,1},
    {9,1,3},
    {1,3,9},
    {1,9,3},
    {3,1,9},
    {3,9,1},
};
struct units
{
    int a=0;
    int b=0;
    int c=0;
};
queue<units> q;
int n;

void solve(int a,int b,int c){
    visited[a][b][c] = 1;
    q.push({a,b,c});
    while(q.size()){
        int aa = q.front().a; int bb = q.front().b; int cc = q.front().c; q.pop();
        if(aa==0 && bb==0 && cc==0) {cout << visited[aa][bb][cc]-1; return;}
        for(int d=0; d<6; d++){
            int na = max(0, aa - dd[d][0]);
            int nb = max(0, bb - dd[d][1]);
            int nc = max(0, cc - dd[d][2]);
            //cout << na<<"," << nb<<","<< nc<<"," << endl;
            if(visited[na][nb][nc]!=0) continue;
            visited[na][nb][nc] = visited[aa][bb][cc] + 1;
            q.push({na,nb,nc});
        }

    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    solve(a[0],a[1],a[2]);
    return 0;
}
