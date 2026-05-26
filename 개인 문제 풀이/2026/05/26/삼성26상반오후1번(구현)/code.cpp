#include <bits/stdc++.h> 
using namespace std; 
int r, c, d;
int n;
int adj[54][54];
int visited[54][54];
bool findall = false;
int dis[54][54]; //bfs용 거리 visited 맵
int tmp_d, best_d;

int dy[4][4] = {
    {-1,0,0,1},
    {1,0,0,-1},
    {0,1,-1,0},
    {0,-1,1,0}
};
int dx[4][4] = {
    {0,-1,1,0},
    {0,1,-1,0},
    {-1,0,0,1},
    {1,0,0,-1}
};

int dyy[4] = {0, 1, 0, -1}; // 좌 하 우 상 ->
int dxx[4] = {-1, 0, 1, 0};

void change_d(int ny, int nx){
    if(ny < r) d = 1; if(ny > r) d = 2; if(nx < c) d = 3; if(nx > c) d = 4;
    d -= 1;
    return;
}

pair<int,int> bfs(int i, int j){
    int ii, jj;
    dis[r][c] = 1;
    pair<int,int> best_pos = {r,c};
    int ret = 9876543;
    queue<pair<int,int>> q;
    q.push({r,c});
    while(q.size()){
        tie(ii,jj) = q.front(); q.pop();
        for(int dd=0; dd<4; dd++){
            int ny = ii + dyy[dd];
            int nx = jj + dxx[dd];
            if(ny<1 || nx<1 || ny>n || nx>n) continue;
            if(adj[ny][nx]) continue;
            if(dis[ny][nx]) continue;
            if(ny<ii) tmp_d = 0; else if(ny>ii) tmp_d = 1;
            else if(nx<jj) tmp_d = 2; else if(nx>jj) tmp_d = 3;
            dis[ny][nx] = dis[ii][jj] + 1;
            q.push({ny,nx});
            bool trash = false;
            if(visited[ny][nx] != 1 && dis[ny][nx] <= ret){ //목적지 후보군 비교
                if(dis[ny][nx] == ret){ //같은데 행이 더 크거나, 행도 같은데 열이 크면 배제
                    if(ny > best_pos.first) {
                        trash = true;
                    }
                    if(ny == best_pos.first){
                        if(nx > best_pos.second){
                            trash = true;
                        }
                    }
                }
                if(!trash){
                    best_pos = {ny, nx};
                    ret = dis[ny][nx];
                    best_d = tmp_d;
                }
            }
        }
    }
    return best_pos;
}

int main() {
    cin >> n;
    cin >> r >> c >> d;
    d -= 1;
    for(int i=1; i<=n; i++){ //1,1 기준
        for(int j=1; j<=n; j++){
            cin >> adj[i][j];
        }
    }
    cout << r << " " << c <<'\n';
    visited[r][c] = 1;
    while(1){
        bool changed = false;
        if(findall) break;
        //인접확인
        for(int dd=0; dd<4; dd++){
            int ny = r + dy[d][dd];
            int nx = c + dx[d][dd];
            if(ny<1 || nx<1 || ny>n || nx>n) continue;
            if(adj[ny][nx]) continue;
            if(visited[ny][nx]) continue;
            change_d(ny, nx);
            r = ny; c = nx;
            changed = true;
            visited[r][c] = 1;
            cout << r << " " << c << '\n';
            //cout << d+1 << ": dirction \n";
            break;
        }
        //인접없으면 2단계
        if(!changed){
            fill(&dis[0][0], &dis[0][0]+54*54, 0);
            pair<int,int> ret = bfs(r,c);
            if(r==ret.first && c==ret.second) break;
            r = ret.first; c = ret.second;
            visited[r][c] = 1;
            d = best_d;
            cout << r << " " << c << endl;
            changed = true;
            //cout << d+1 <<'\n';
        }
        if(!changed) findall = true;
    }

    return 0;
}
