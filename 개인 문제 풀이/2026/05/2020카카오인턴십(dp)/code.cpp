#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;
int dp[26][26][4];
bool visited[26][26];
int n;
#define INF 987654321
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};

void cal(int i, int j, int d,int cost, vector<vector<int>>& adj){
    if(dp[i][j][d]<=cost) return;
    dp[i][j][d] = cost;
    if(i==n-1 && j==n-1){
        return;
    }
    
    for(int dd=0; dd<4; dd++){
        int ny = i + dy[dd];
        int nx = j + dx[dd];
        if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
        if(adj[ny][nx]) continue;
        int s = dd;
        int next_cost = cost + (d == s ? 100 : 600);
        cal(ny, nx, s, next_cost, adj);
    }
}

int solution(vector<vector<int>> board) {
    n = board[0].size();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            for(int d=0; d<4; d++){
                dp[i][j][d] = INF;
            }
        }
    }
    cal(0, 0, 1, 0, board);
    cal(0, 0, 2, 0, board);
    int answer = INF;
    for(int d=0; d<4; d++){
        answer = min(answer, dp[n-1][n-1][d]);
    }
    return answer;
}
