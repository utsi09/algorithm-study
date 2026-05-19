#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[20][20][3]; //x,y,state
int dx[3] = {1,1,0};
int dy[3] = {0,1,1};
int visited[20][20][3];
int N;
int adj[20][20];

vector<vector<int>> next_d = {
    {0,1},
    {0,1,2},
    {1,2}
};

int dfs(int i, int j, int state){
    if(i == N && j == N) return 1;

    if(dp[i][j][state] != -1) return dp[i][j][state];

    dp[i][j][state] = 0; //초기화
    for(int d: next_d[state]){ //갈수있는 state 꺼내기
        bool can_go = true;
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(ny<1 || nx<1 || ny>N || nx>N) continue;
        if(d == 1){ //대각 
            for(int dd=0; dd<3; dd++){
                if(adj[i+dy[dd]][j+dx[dd]]) can_go = false;
            }
            if(!can_go) continue;
        }
        else if(adj[ny][nx]) continue;

        dp[i][j][state] += dfs(ny,nx,d);
    }
    return dp[i][j][state];
}

int main() {
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >>adj[i][j];
        }
    }
    memset(dp ,-1, sizeof(dp));
    
    cout << dfs(1,2,0);
    return 0;
}
