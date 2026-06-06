#include <bits/stdc++.h>
using namespace std;
int r, c;
int adj[101][101];
int visited[101][101];
int cnt;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

int ii, jj;
int remained=0;


void bfs(int i, int j){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(q.size()){
        tie(ii,jj) = q.front(); q.pop();
        for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            if(ny<0 || nx<0 || ny>=r || nx>=c) continue;
            if(visited[ny][nx]) continue;
            if(adj[ny][nx] == 1){
                visited[ny][nx] = 2; //공기 접촉된 칸은 2
                continue;
            }
            visited[ny][nx] = 1;
            q.push({ny,nx});
        }

    }
    return;
}

bool remove_cheese(){
    int now_remained = 0;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            if(adj[i][j] == 1 && visited[i][j] == 2){
                adj[i][j] = 0;
            }
            if(adj[i][j] == 1 && visited[i][j] == 0){ //남아있는 치즈 칸
                now_remained++;
            }
        }
    }
    if(now_remained <= 0){
        return false;
    }
    else{
        remained = now_remained;
        return true;
    }
}

int main(){
    cin >> r >> c;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cin >> adj[i][j];
            if(adj[i][j] == 1) remained++;
        }
    }
    for(;;cnt++){
        fill(&visited[0][0], &visited[0][0]+101*101, 0);
        bfs(0,0);
        if(!remove_cheese()) break;
        // cout << "-------------\n";
        // for(int i=0; i<r; i++){
        //     for(int j=0; j<c; j++){
        //         cout << adj[i][j] <<" ";
        //     }
        //     cout <<'\n';
        // }
    }
    cout << cnt+1 <<'\n';
    cout << remained;

    return 0;
}
