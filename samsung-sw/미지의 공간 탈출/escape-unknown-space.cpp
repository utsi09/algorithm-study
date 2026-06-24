#include <bits/stdc++.h>
using namespace std;
int bot[21][21];
int mid[11][11*4]; //4개 이어붙인 시간의 벽
int top[11][11];
int n,m,f;
int s_i, s_j; //시간맵좌표에서 좌상단
int dy[4] = {0,0,1,-1}; //동서남북
int dx[4] = {1,-1,0,0}; 
int tmp[5][11][11]; //임시로 담아둔 시간의 공간
int tmp_goal_i, tmp_goal_j; //시간의공간 중간 탈출소
const int INF = 1e9;
int ab_map[21][21];
int start_i, start_j;
int visited[3][44][44];
int goal_i, goal_j;
int table_hash[4] = {1,3,0,2}; //mid 대입 순서

struct Node {
    int r,c;
    int div;
};


void db_visited_map(){
    for(int d=0; d<3; d++){
        if(d==0){
            for(int i=0; i<m; i++){
                for(int j=0; j<m; j++){
                    cout << visited[0][i][j] << " ";
                }
                cout << '\n';
            }
        }
        if(d==1){
            for(int i=0; i<m; i++){
                for(int j=0; j<m*4; j++){
                    cout << visited[1][i][j] << " ";
                }
                cout << '\n';
            }
        }
        if(d==2){
            for(int i=0; i<n; i++){
                for(int j=0; j<n; j++){
                    cout << visited[2][i][j] << " ";
                }
                cout << '\n';
            }
        }
    }
}

struct abnormal //이상 현상
{
    int r,c,d,v;
};

vector<abnormal> abnos;

void db_ab_map(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << ab_map[i][j] << " ";
        }
        cout << '\n';
    }
}

void db_mid_map(){
    for(int i=0; i<m; i++){
        for(int j=0; j<m*4; j++){
            cout << mid[i][j] << " ";
        }
        cout << '\n';
    }
    cout << s_i<<","<< s_j << "\n";
}


int bfs(int i, int j, int div){ //div 0 : top, 1: mid, 2: bot
    int n_i, n_j, cur_dv;
    memset(visited, -1, sizeof(visited));
    visited[div][i][j] = 0;
    queue<Node> q;
    q.push({i,j,div});
    while(q.size()){
        Node tmp = q.front(); q.pop();
        int cur_dv = tmp.div; int n_i = tmp.r; int n_j = tmp.c;
        if(visited[2][goal_i][goal_j] != -1) return visited[2][goal_i][goal_j]; //목적지 도달시
        for(int d=0; d<4; d++){
            int nd = cur_dv;
            int ny = n_i + dy[d];
            int nx = n_j + dx[d];
            if(cur_dv == 0){ // top
                if(nx >= m){ // 동
                    ny = 0;
                    nx = m + ((m - 1) - n_i);
                    nd = 1;
                }
                else if(nx < 0){ // 서
                    ny = 0;
                    nx = 3 * m + n_i;
                    nd = 1;
                }
                else if(ny >= m){ // 남
                    ny = 0;
                    nx = n_j;
                    nd = 1;
                }
                else if(ny < 0){ // 북
                    ny = 0;
                    nx = (m-1)-n_j + 2 * m;
                    nd = 1;
                }

                if(nd == 1){
                    if(mid[ny][nx] == 1) continue;
                }
                else {
                    if(ny < 0 || nx < 0 || ny >= m || nx >= m) continue;
                    if(top[ny][nx] == 1) continue;
                }

                if(visited[nd][ny][nx] != -1) continue;

                visited[nd][ny][nx] = visited[cur_dv][n_i][n_j] + 1;
                q.push({ny, nx, nd});
            }
            else if(cur_dv == 1){
                if(nx < 0){
                    nx = 4 * m - 1;
                }
                else if(nx >= 4 * m){
                    nx = 0;
                }

                int nt = visited[cur_dv][n_i][n_j] + 1;

                if(ny >= m){ 
                    // 옆에서 바닥
                    int face = nx / m;
                    int k = nx % m;
                    nd = 2;
                    if(face == 0){ // 남
                        ny = s_i + m;
                        nx = s_j + k;
                    }
                    else if(face == 1){ // 동
                        ny = s_i + (m-1-k);
                        nx = s_j + m;
                    }
                    else if(face == 2){ // 북
                        ny = s_i - 1;
                        nx = s_j + (m-1-k);
                    }
                    else if(face == 3){ // 서
                        ny = s_i + k;
                        nx = s_j - 1;
                    }
                }
                else if(ny < 0){
                    // 옆에서 천장
                    int face = nx / m;
                    int k = nx % m;
                    nd = 0;
                    if(face == 0){ // 3
                        ny = m - 1;
                        nx = k;
                    }
                    else if(face == 1){ // 0
                        ny = m-1 - k; //
                        nx = m-1;
                        
                    }
                    else if(face == 2){ // 2
                        ny = 0;
                        nx = m-1 - k;
                    }
                    else if(face == 3){ // 1
                        ny = k;
                        nx = 0;
                    }
                }

                if(nd == 0){
                    if(top[ny][nx] == 1) continue;
                }
                else if(nd == 1){
                    if(ny < 0 || nx < 0 || ny >= m || nx >= 4 * m) continue;
                    if(mid[ny][nx] == 1) continue;
                }
                else if(nd == 2){
                    //cout << ny << "," << nx << " : arrived \n";
                    if(ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
                    if(bot[ny][nx] == 1 || bot[ny][nx] == 3) continue;
                    if(nt >= ab_map[ny][nx]) continue;
                }

                if(visited[nd][ny][nx] != -1) continue;

                visited[nd][ny][nx] = nt;
                q.push({ny, nx, nd});
            }
            else if(cur_dv == 2){
                if(ny<0 || nx<0 || ny>=n || nx>=n) continue; //오버플로우
                if(bot[ny][nx] == 1 || bot[ny][nx] == 3) continue; //장애물
                
                if(visited[cur_dv][n_i][n_j] + 1 >= ab_map[ny][nx]) continue; //이상현상
                if(visited[nd][ny][nx] != -1) continue;
                visited[nd][ny][nx] = visited[cur_dv][n_i][n_j] + 1;
                q.push({ny,nx,nd});
            }
        }
    }

    return -1; //탈출 실패
}

int main() {
    cin >> n >> m >> f;
    bool checker = false;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> bot[i][j];
            if(bot[i][j] == 4){
                goal_i = i;
                goal_j = j;
            }
            if(checker == false && bot[i][j] == 3){
                s_i = i;
                s_j = j;
                checker = true;
            }
        }
    } //시간의 공간 좌상단 좌표와 미지의 공간 맵 입력

    
    for(int i=0; i<5; i++){ //top 과 mid 저장
        int insert_idx = table_hash[i];
        //cout << insert_idx << ": idx\n";
        for(int r=0; r<m; r++){
            for(int c=0; c<m; c++){
                int this_c = c + insert_idx * m; 
                if(i==4){
                    cin >> top[r][c];
                    if(top[r][c] == 2){ //시작 위치 저장
                        start_i = r;
                        start_j = c;
                        top[r][c] = 0;
                    }
                }
                else{
                    cin >> mid[r][this_c];
                }    
            }
        }
    } //임시로 시간의 공간 저장

    //db_mid_map();
    
    for(int ab=0; ab<f; ab++){
        abnormal tmp_ab;
        cin >> tmp_ab.r >> tmp_ab.c >> tmp_ab.d >> tmp_ab.v;
        abnos.push_back(tmp_ab);
    }
    fill(&ab_map[0][0], &ab_map[0][0] + 21 * 21, INF);
    for(abnormal tmp_ab : abnos){ //ab_map에 막히는 시간 저장
        int ii=tmp_ab.r;
        int jj=tmp_ab.c;
        int dd=tmp_ab.d;
        int vv=tmp_ab.v;
        ab_map[ii][jj] = min(ab_map[ii][jj], 0); //1분 부터 시작
        int t = vv;
        while(1){
            int ny=ii+dy[dd];
            int nx=jj+dx[dd];
            if(ny<0 || nx<0 || ny>=n|| nx>=n) break;
            if(bot[ny][nx] == 1 || bot[ny][nx] == 3 || bot[ny][nx] == 4) break; //장애물 , 탈출구
            ab_map[ny][nx] = min(ab_map[ny][nx], t); //덮어쓰기 방지
            ii = ny; jj = nx;
            t+=vv;
        }
    }
    
    cout << bfs(start_i, start_j, 0) << '\n';
    //db_visited_map();
    return 0;
}