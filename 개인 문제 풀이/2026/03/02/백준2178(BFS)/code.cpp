#include <bits/stdc++.h>

using namespace std;
const int map_size = 100;
int adj[map_size][map_size];
int visited[map_size][map_size];

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int end_y = 0, end_x = 0;
int y=0, x=0;

void BFS(int i, int j){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push(make_pair(i,j));
    while(q.size()){
        tie(y,x) = q.front(); q.pop();
        for(int k=0; k<4; k++){
            int there_y = y+dy[k];
            int there_x = x+dx[k];
            if (there_y<0 || there_y>=100 || there_x<0 || there_x>=100) continue;
            if (adj[there_y][there_x] == 0 || visited[there_y][there_x]!=0) continue;
            visited[there_y][there_x] = visited[y][x] + 1;
            // cout << there_y << there_x << endl;
            q.push(make_pair(there_y, there_x));
        }
    }
}

int main() {
    scanf("%d %d",&end_y, &end_x);
    for(int i=0; i<end_y; i++){
        for(int j=0; j<end_x; j++){
            scanf("%1d", &adj[i][j]);
        }
    }

    BFS(0,0);
    printf("%d", visited[end_y-1][end_x-1]);
    return 0;
}
