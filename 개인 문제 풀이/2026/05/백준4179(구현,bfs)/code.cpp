#include <bits/stdc++.h> 
using namespace std;
#define INF 987654321
char adj[1004][1004];
int fire_map[1004][1004]; //불의 최단거리
int jh[1004][1004];
int dy[4] = {-1,0,1,0}; int dx[4] = {0,1,0,-1};
int r,c;
queue<pair<int,int>> q;
int sx, sy; //지훈이 위치
int y, x;
int ret = 0;

int main(){
    fill(&fire_map[0][0], &fire_map[0][0]+1004*1004, INF);
    cin >> r >> c;
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            char tmp; cin >> tmp;
            if(tmp == 'F'){
                q.push({i,j});
                fire_map[i][j] = 1;
            }
            else if(tmp == 'J'){
                sy = i; sx = j;
            }
            adj[i][j] = tmp;
        }
    }
    
    while(q.size()){
        tie(y,x) = q.front(); q.pop();
        //cout << y << x << endl;
        for(int d=0; d<4; d++){
            int ny = y + dy[d]; int nx = x + dx[d];
            if(ny<0 || nx<0 || ny>=r || nx>=c) continue;
            if(fire_map[ny][nx] != INF) continue;
            if(adj[ny][nx] == '#') continue;
            fire_map[ny][nx] = fire_map[y][x] + 1;
            q.push({ny,nx});
        }
    }
    // for(int i=0; i<r; i++){
    //     for(int j=0; j<c; j++){
    //         cout << fire_map[i][j]<< " ";
    //     }
    //     cout << endl;
    // }
    //cout << "out loop1\n";
    q.push({sy,sx});
    jh[sy][sx] = 1;
    while(q.size()){
        tie(y,x) = q.front(); q.pop();
        if(y == 0 || x == 0 || y == r-1 || x == c-1){
            ret = jh[y][x];
            break;
        }
        for(int d=0; d<4; d++){
            int ny = y + dy[d]; int nx = x + dx[d];
            if(ny<0 || nx<0 || ny>=r || nx>=c) continue;
            if(jh[ny][nx] != 0) continue;
            if(adj[ny][nx] == '#') continue;
            if(jh[y][x] + 1 >= fire_map[ny][nx]) continue;
            //cout << "can move\n";
            jh[ny][nx] = jh[y][x] + 1;
            q.push({ny,nx});
        }
    }
    if(ret == 0) cout << "IMPOSSIBLE";
    else cout << ret;

    return 0;
}
