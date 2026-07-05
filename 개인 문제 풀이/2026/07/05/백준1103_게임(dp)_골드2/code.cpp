#include <bits/stdc++.h>
using namespace std;
int n,m;
int adj[51][51]; //숫자맵
int dp[51][51];
int visited[51][51];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int solve(int i, int j){
    if(i < 0 || j < 0 || i >= n || j >= m || adj[i][j] == 0){
        return 0;
    }
    if(visited[i][j] == 1){
        cout << "-1";
        exit(0);
    }
    int& here = dp[i][j];
    if(here != -1) return here;
    visited[i][j] = 1;
    for(int d=0; d<4; d++){
        int ny = i + dy[d] * adj[i][j];
        int nx = j + dx[d] * adj[i][j];
        here = max(here, solve(ny,nx) + 1);
    }
    visited[i][j] = 0;
    return here;
}



int main(){
    cin >> n >> m; 
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            char tmp; cin >> tmp;
            if(tmp == 'H'){
                adj[i][j] = 0;
            }
            else{
                adj[i][j] = tmp - 48;
            }
            
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << solve(0,0);


}
