#include <bits/stdc++.h>
using namespace std;
#define MAXN 98765432
int n;
int adj[17][17];
int dp[17][1<<17];

int travel(int now, int visited){
    if(visited == (1 << n) - 1){ //모든 도시 방문시
        if(adj[now][0] == 0){
            return MAXN;
        }
        else return adj[now][0];
    }
    int& here = dp[now][visited];
    if(here != -1) return here;
    here = MAXN;
    for(int i=1; i<n; i++){
        if(visited & (1<<i) || !adj[now][i]){ //이미 방문 or 못가는 곳
            continue;
        }
        int next = visited | (1<<i);
        here = min(here, travel(i, next) + adj[now][i]);
    }
    return here;
}


int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << travel(0, 1);

    return 0;
}
