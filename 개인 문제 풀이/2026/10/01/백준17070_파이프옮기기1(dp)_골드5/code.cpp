#include <bits/stdc++.h>
using namespace std;
#define MAXN 98765432
int n;
int adj[17][17];
int dp[17][17][3];
//state : 0가로 1대각 2세로
int dy[3] = {0, 1, 1};
int dx[3] = {1, 1, 0};
int ret; 

int solve(int i, int j, int state){
    if(i==n-1 && j==n-1){
        return 1;
    }
    int& here = dp[i][j][state];
    if(here != -1) return here;
    here = 0;
    for(int d=0; d<3; d++){
        if(abs(state - d) > 1){ //2번회전 불가능
            continue;
        }
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(ny>=n || nx>=n || adj[ny][nx]) continue; //오버플로우, 벽
        bool check_three = false;
        if(d == 1){
            for(int dd=0; dd<3; dd++){
                if(adj[i + dy[dd]][j + dx[dd]]) check_three = true;
            }
        }
        if(check_three) continue;
        here += solve(ny, nx, d);
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
    cout << solve(0,1,0);

    return 0;
}
