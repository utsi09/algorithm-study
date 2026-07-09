#include <bits/stdc++.h>
using namespace std;
int n, r, c, d;
int adj[51][51];
int visited[51][51];
int bfs_visited[51][51]; //bfs용

int cnt; //종료 조건 : 0 되면 

int dy[4] = {-1, 1, 0, 0}; //상하좌우
int dx[4] = {0, 0, -1, 1};

int dy2[4] = {0,1,0,-1}; //좌하우상 2단계 이동용
int dx2[4] = {-1,0,1,0};

int goal_y, goal_x; //2단계 목표 바다

void db_map(){
    cout << "------map------\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i == r && j ==c){
                cout << "W ";
                continue;
            }
            cout << visited[i][j] << " ";
        }
        cout <<'\n';
    }
    cout << "------map------\n";
    return;
}


int hsmap[4][4] = {
    {0,2,3,1},
    {1,3,2,0},
    {2,1,0,3},
    {3,0,1,2}
};

int get_d(int ny, int nx){
    int dis_r = ny - r;
    int dis_c = nx - c;
    if(dis_r > 0) return 1;
    if(dis_r < 0) return 0;
    if(dis_c > 0) return 3;
    if(dis_c < 0) return 2;
}

bool adj_search(){
    for(int dd=0; dd<4; dd++){
        //cout << d <<'\n';
        int direction = hsmap[d][dd];
        //cout << direction <<'\n';
        int ny = r + dy[direction];
        int nx = c + dx[direction];
        //cout << "search : " << ny+1 << "," << nx+1 << '\n'; 
        if(ny<0 || nx<0 || ny>= n || nx>= n) continue;
        if(adj[ny][nx]) continue;
        if(visited[ny][nx]) continue;
        d = get_d(ny,nx);
        r = ny;
        c = nx;
        cnt--;
        visited[r][c] = 1;
        cout << r+1 << " " << c+1 << '\n';
        return true; //인접한 곳 있음
    }
    return false;
}

void bfs(int sy, int sx, int f){
    bfs_visited[sy][sx] = 1;
    queue<pair<int,int>> q;
    q.push({sy,sx});
    int best_d = 98765432;
    while(q.size()){
        int ii = q.front().first;
        int jj = q.front().second;
        q.pop();
        if(f == 0 && visited[ii][jj] == 0){ //서치 && 처음 탐험한 바다
            if(bfs_visited[ii][jj] < best_d){ //최단거리
                goal_y = ii;
                goal_x = jj;
                best_d = bfs_visited[ii][jj];
            }
            else if(bfs_visited[ii][jj] == best_d){
                if(goal_y < ii) continue; //행번호 더 크면 거름
                if(goal_y == ii && goal_x < jj) continue; // 행번호같은데 열 번호 더크면 거름
                goal_y = ii;
                goal_x = jj;
            }
        }
        for(int dd=0; dd<4; dd++){
            int ny = ii + dy[dd];
            int nx = jj + dx[dd];
            if(ny<0 || nx<0 || ny>=n || nx>=n || bfs_visited[ny][nx]) continue;
            if(adj[ny][nx]) continue;
            q.push({ny,nx});
            bfs_visited[ny][nx] = bfs_visited[ii][jj] + 1;
        }
    }
    return;
}

void jump_search(){
    fill(&bfs_visited[0][0], &bfs_visited[0][0] + 51*51, 0);
    goal_y = -1; goal_x = -1;
    bfs(r,c,0); // 골 탐색용

    while(1){
        if(r == goal_y && c == goal_x) {
            cout << r+1 << " " << c+1 << '\n';
            visited[r][c] = 1;
            cnt--;
            break;
        }
        fill(&bfs_visited[0][0], &bfs_visited[0][0] + 51*51, 0);
        bfs(goal_y, goal_x, 1); //bfs_visited 를 코스트맵으로 활용
        int best_d = 98765432;
        int best_dd = -1;
        for(int dd=0; dd<4; dd++){
            int ny = r + dy2[dd];
            int nx = c + dx2[dd];
            if(ny <0 || nx<0 || ny>=n || nx>=n) continue;
            if(adj[ny][nx]) continue;
            if(bfs_visited[ny][nx] < best_d){
                best_dd = dd;
                best_d = bfs_visited[ny][nx];
            }
        }
        if(best_dd != -1){
            d = get_d(r+dy2[best_dd], c+dx2[best_dd]);
            r += dy2[best_dd];
            c += dx2[best_dd];
        }
        
    }
    
    return;
}


int main(){
    cin >> n >> r >> c >> d;
    d--;
    r--;
    c--;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
            if(adj[i][j] != 1) cnt++; //방문할수있는 바다
        }
    }
    cout << r+1 << " " << c+1 <<'\n';
    visited[r][c] = 1;
    cnt--;
    while(1){
        //db_map();
        //cout << cnt << " : cnt\n";
        if(cnt == 0) return 0; //남은 바다가 없으면 종료

        if(!adj_search()){ // 1. 인접 탐험
            jump_search(); // 2. 가장 가까운 바다로 이동
            //cout << goal_y+1 << "," << goal_x+1 << " : goal! \n";
        }

    }
    


    return 0;
}