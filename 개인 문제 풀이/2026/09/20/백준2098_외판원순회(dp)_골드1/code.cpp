#include <bits/stdc++.h>
using namespace std;
int n;
int dis[20][20];
int dp[20][1<<21];

int solve(int here, int visited){
    if(visited == (1 << n) - 1){ //모든 도시 방문
        if(dis[here][0] == 0){
            return 98765432;
        }
        return dis[here][0];
    }

    int& saved = dp[here][visited];
    if(saved != -1){
        return saved;
    }
    saved = 98765432;
    for(int i=0; i<n; i++){
        //방문했는지
        if(dis[here][i] == 0) continue;
        if(visited & (1<<i)) continue;
        int next = visited | (1<<i);
        saved = min(saved, solve(i, next) + dis[here][i]);
    }
    return saved;
}


int main(){
    cin >> n;

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> dis[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(0, 1);

    return 0;
}
