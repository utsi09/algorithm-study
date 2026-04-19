#include <bits/stdc++.h>
using namespace std;
int n,m;
const int m_size = 51;
int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
char adj[m_size][m_size];
int visited[m_size][m_size];
int cnt = 0;
int x,y;

void bfs(int i, int j){
    fill(&visited[0][0], &visited[0][0]+m_size*m_size, 0);
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(q.size()){
        tie(y,x) = q.front(); q.pop();
        for(int d=0; d<4; d++){
            int ny = y + dy[d];
            int nx = x + dx[d];
            if(ny<0 || nx<0 || ny>=n || nx>=m) continue;
            if(visited[ny][nx] != 0) continue;
            if(adj[ny][nx] == 'W') continue;
            visited[ny][nx] = visited[y][x] + 1;
            q.push({ny,nx});
            cnt = max(cnt, visited[ny][nx]-1);
        }
    }
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            scanf(" %c",&adj[i][j]);
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(adj[i][j] == 'W') continue;
            bfs(i,j);
        }
    }
    cout << cnt;
    return 0;
}
