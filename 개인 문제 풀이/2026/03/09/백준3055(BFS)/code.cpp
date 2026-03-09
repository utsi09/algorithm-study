#include <bits/stdc++.h>
using namespace std;
int R=0,C=0;
const int map_size = 51;
char adj[map_size][map_size];
int visited[map_size][map_size];

pair<int,int> s_pos;
pair<int,int> e_pos;
vector<pair<int,int>> water;

int water_map[map_size][map_size];

int w_x=0, w_y=0;
int x=0, y=0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

void water_BFS(){
    queue<pair<int,int>> q;
    for(auto& here_water : water){
        water_map[here_water.first][here_water.second] = 0;
        pair<int,int> tmp = make_pair(here_water.first,here_water.second);
        q.push(tmp);
    }
    
    while(q.size()){
        tie(y,x) = q.front(); q.pop();
        for(int k=0; k<4; k++){
            int nx= x+dx[k];
            int ny= y+dy[k];
            if (ny<0 || ny>=R || nx<0 || nx>=C) continue;
            if (adj[ny][nx] == '*' || adj[ny][nx] == 'X' || adj[ny][nx] == 'S' || adj[ny][nx] == 'D') continue; // 물, 돌, 고슴도치
            if (water_map[ny][nx] != 987654321) continue;
            water_map[ny][nx] = water_map[y][x] +1;
            q.push(make_pair(ny,nx));
        }
    }
}   

void BFS(int i, int j){
    queue<pair<int,int>> q;
    pair<int,int> tmp = make_pair(i,j);
    q.push(tmp);
    while(q.size()){
        tie(y,x) = q.front(); q.pop();
        for(int k=0; k<4; k++){
            int nx= x+dx[k];
            int ny= y+dy[k];
            if (ny<0 || ny>=R || nx<0 || nx>=C) continue;
            if (adj[ny][nx] == '*' || adj[ny][nx] == 'X') continue; // 물, 돌
            if (visited[ny][nx] != -1 || visited[y][x] + 1 >= water_map[ny][nx]) continue;
            visited[ny][nx] = visited[y][x] +1;
            q.push(make_pair(ny,nx));
        }
    }
}

int main(){
    fill(&water_map[0][0], &water_map[0][0] + map_size * map_size, 987654321);
    fill(&visited[0][0], &visited[0][0] + map_size * map_size, -1);
    cin >> R >> C;
    for (int i=0; i<R; i++){
        for (int j=0; j<C; j++){
            char input;
            cin >> input;
            if (input =='S') s_pos = make_pair(i,j);
            if (input =='D') e_pos = make_pair(i,j);
            if (input =='*') water.push_back(make_pair(i,j));

            adj[i][j] = input;
        }
    }


    water_BFS();
    visited[s_pos.first][s_pos.second] = 0;
    BFS(s_pos.first, s_pos.second);
    
    if (visited[e_pos.first][e_pos.second] == -1) cout << "KAKTUS" << endl;
    else cout << visited[e_pos.first][e_pos.second] << endl;
    return 0;
}
