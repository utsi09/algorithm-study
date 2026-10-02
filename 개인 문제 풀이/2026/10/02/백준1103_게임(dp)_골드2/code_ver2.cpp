#include <bits/stdc++.h>
using namespace std;
#define MAXN 98765432

int n, m;
int adj[51][51];
int dp[51][51];
int visited[51][51];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
bool is_repeat = false;

//2312 반례 찾았음 
int throw_coin(int i, int j){
    if(visited[i][j]){
        is_repeat = true;
        return MAXN;
    }

    int& here = dp[i][j];
    if(here != -1){ //방문한적있으면
        return here;
    }
    visited[i][j] = 1;
    here = 0;
    for(int d=0; d<4; d++){
        int ny = i + (dy[d] * adj[i][j]);
        int nx = j + (dx[d] * adj[i][j]);
        if(ny<0 || ny>=n || nx<0 || nx>=m || !adj[ny][nx]) continue;

        here = max(here, throw_coin(ny, nx) + 1);
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
                adj[i][j] = tmp - '0';
            }
        }
    }
    memset(dp, -1, sizeof(dp));
    int ret = throw_coin(0,0) + 1;
    if(is_repeat){
        cout << "-1";
        return 0;
    }
    cout << ret;

    return 0;
}
