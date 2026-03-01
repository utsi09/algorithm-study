#include <bits/stdc++.h>
using namespace std;

int n=0, m=0;
int start_x=0, start_y=0;
int end_x=0, end_y=0;

const int map_size = 100;
int adj[map_size][map_size];
int visited[map_size][map_size];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};


void BFS(int y, int x){
    queue<pair<int,int>> q;
    pair<int,int> p = make_pair(y,x);
    q.push(p);
    while(q.size()){
        int y_1 = q.front().first; //y = i
        int x_1 = q.front().second; // x = j
        q.pop();
        for(int k=0;k<4;k++){
            int y_2 = y_1 + dy[k];
            int x_2 = x_1 + dx[k];
            if (x_2 < 0 || x_2 >= 100 || y_2 < 0 || y_2 >= 100) continue;
            if (adj[y_2][x_2]==0 || visited[y_2][x_2]!=0) continue;
            pair<int,int> tmp_pair = make_pair(y_2, x_2);
            q.push(tmp_pair);
            visited[y_2][x_2] = visited[y_1][x_1] + 1;
        }
        
    }
}

int main(){
    cin >> n >> m;
    cin >> start_x >> start_y;
    cin >> end_x >> end_y;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> adj[i][j];
        }
    }
    visited[start_y][start_x] = 1;
    BFS(start_y,start_x);

    cout << visited[end_y][end_x] << endl;
    return 0;
}
