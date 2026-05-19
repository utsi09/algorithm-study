#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[20][20][3]; //x,y,state
int N;
int adj[20][20];

bool check(int i, int j, int state){
    if(adj[i][j]) return false;
    if(i<1 || j<1 || i>N || j>N) return false;
    if(state == 1){
        if(adj[i-1][j] || adj[i][j-1]) return false;
    }
    return true;
}

int main() {
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >>adj[i][j];
        }
    }
    dp[1][2][0] = 1;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(check(i,j+1,0)) dp[i][j+1][0] += dp[i][j][0];
            if(check(i+1,j+1,1)) dp[i+1][j+1][1] += dp[i][j][0];

            if(check(i+1,j,2)) dp[i+1][j][2] += dp[i][j][2];
            if(check(i+1,j+1,1)) dp[i+1][j+1][1] += dp[i][j][2];

            if(check(i,j+1,0)) dp[i][j+1][0] += dp[i][j][1];
            if(check(i+1,j+1,1)) dp[i+1][j+1][1] += dp[i][j][1];
            if(check(i+1,j,2)) dp[i+1][j][2] += dp[i][j][1];
        }
    }
    
    cout << dp[N][N][0] + dp[N][N][1] + dp[N][N][2];

    return 0;
}
