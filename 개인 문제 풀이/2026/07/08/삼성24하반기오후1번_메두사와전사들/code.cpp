#include <bits/stdc++.h>
using namespace std;
#define INF 98765432
int n,m;
int sr, sc, er, ec;
int adj[51][51];
int visited[51][51];
int stoned_map[4][51][51];
//int real_stoned_map[51][51];
int best_map_idx = -1;

struct mob{
    int r,c;
    bool is_stone = false;
    bool is_die = false;
};
vector<mob> mobs;
int dy[4] = {-1, 1, 0, 0}; //상하좌우
int dx[4] = {0, 0, -1, 1};

int dy2[4] = {0,0,-1,1}; //좌우상하
int dx2[4] = {-1,1,0,0};

vector<int> best_stoned;
int cnt_d, cnt_s, cnt_a; //이번턴의 이동한거리합, 돌이된 몹, 메두사를 공격한 몹

int bfs(int y, int x){
    visited[y][x] = 1;
    queue<pair<int,int>> q;
    q.push({y,x});
    while(q.size()){
        
        int ii = q.front().first;
        int jj = q.front().second;
        q.pop();
        if(ii == er && jj == ec){
            return visited[ii][jj];
        }
        for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            if(ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            if(visited[ny][nx] != 0) continue;
            if(adj[ny][nx] == 1) continue;
            q.push({ny,nx});
            visited[ny][nx] = visited[ii][jj] + 1;
        }   
    }
    return INF;
}

int mob_bfs(int y, int x, int ey, int ex, int t){
    return abs(y - ey) + abs(x - ex);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    cin >> sr >> sc >> er >> ec;
    mob tmp;
    for(int i=0; i<m; i++){
        cin >> tmp.r >> tmp.c;
        mobs.push_back(tmp);
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }
    while(1){
        //초기화
        cnt_d = 0;
        cnt_s = 0;
        cnt_a = 0;
        // 1. 메두사의 이동
        int best_d = -1;
        int best_ret = INF;
        for(int d=0; d<4; d++){
            int ny = sr + dy[d];
            int nx = sc + dx[d];
            if(ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
            if(adj[ny][nx] == 1) continue;
            fill(&visited[0][0], &visited[0][0] + 51*51, 0);
            int ret = bfs(ny, nx);
            if(ret < best_ret){
                best_d = d; //방향 갱신
                best_ret = ret; // ret 갱신
            }
        }
        if(best_ret == INF){ //공원까지의 도로가 존재하지않는 경우
            cout << -1;
            exit(0);
        }
        sr += dy[best_d];
        sc += dx[best_d];
        for(mob& m : mobs){ //그자리의 몹 사망
            if(m.is_die == false && m.r == sr && m.c == sc){
                m.is_die = true;
            }
        }
        if(sr == er && sc == ec){ //도착
            cout << "0";
            exit(0);
        }

        int best_s = 0; // 베스트 방향의 돌이된 몹의 수 
        int look = -1;
        //2. 메두사의 시선
        int leftt, rightt;
        int m_leftt, m_rightt;
        vector<int> this_stoned;
        fill(&stoned_map[0][0][0], &stoned_map[0][0][0] + 4*51*51, 0);
        
        for(int d=0; d<4; d++){
            this_stoned.erase(this_stoned.begin(), this_stoned.end());
            int this_s = 0;
            if(d == 0){ //상  
                leftt = sc - 1;
                rightt = sc + 1;
                for(int i = sr + dy[d]; i>= 0 ; i--){
                    for(int j = leftt; j<= rightt; j++){
                        if(stoned_map[d][i][j] == -1) continue; // 이미 그림자면 할거없음 패스
                        for(int idx=0; idx<mobs.size(); idx++){
                            mob m = mobs[idx];
                            if(m.is_die) continue;
                            if(m.r == i && m.c == j){ //몹과 영역이 만났을 경우
                                this_s++; //임시 돌이 될 몹 개수 증가
                                this_stoned.push_back(idx); //임시 돌이 될 몹 좌표 저장
                                stoned_map[d][m.r][m.c] = 1; //몹이 돌이 된것도 시야에 포함
                                if(m.c < sc){
                                    m_leftt = m.c - 1;
                                    for(int ii = m.r + dy[d]; ii >= 0; ii--){
                                        for(int jj = m_leftt; jj <= m.c; jj++){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_leftt - 1 >= 0) m_leftt--;
                                    }
                                }
                                else if(m.c == sc){
                                    for(int ii = m.r + dy[d]; ii>= 0; ii--){
                                        stoned_map[d][ii][m.c] = -1;
                                    }
                                }
                                else if(m.c > sc){
                                    m_rightt = m.c + 1;
                                    for(int ii = m.r + dy[d]; ii >= 0; ii--){
                                        for(int jj = m_rightt; jj >= m.c; jj--){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_rightt + 1 < n) m_rightt++;
                                    }
                                }
                            }
                        }
                        stoned_map[d][i][j] = 1; //몹의 그림자가 아니면 색칠
                    }
                    if(leftt - 1 >= 0) leftt--;
                    if(rightt + 1 < n) rightt++;
                }
            }
            else if(d == 1){ //하
                leftt = sc - 1;
                rightt = sc + 1;
                for(int i = sr + dy[d]; i < n ; i++){
                    for(int j = leftt; j<= rightt; j++){
                        if(stoned_map[d][i][j] == -1) continue; // 이미 그림자면 할거없음 패스
                        for(int idx=0; idx<mobs.size(); idx++){
                            mob m = mobs[idx];
                            if(m.is_die) continue;
                            if(m.r == i && m.c == j){ //몹과 영역이 만났을 경우
                                this_s++; //임시 돌이 될 몹 개수 증가
                                this_stoned.push_back(idx); //임시 돌이 될 몹 인덱스 저장
                                stoned_map[d][m.r][m.c] = 1; //몹이 돌이 된것도 시야에 포함
                                if(m.c < sc){
                                    m_leftt = m.c - 1;
                                    for(int ii = m.r + dy[d]; ii < n; ii++){
                                        for(int jj = m_leftt; jj <= m.c; jj++){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_leftt - 1 >= 0) m_leftt--;
                                    }
                                }
                                else if(m.c == sc){
                                    for(int ii = m.r + dy[d]; ii < n; ii++){
                                        stoned_map[d][ii][m.c] = -1;
                                    }
                                }
                                else if(m.c > sc){
                                    m_rightt = m.c + 1;
                                    for(int ii = m.r + dy[d]; ii < n; ii++){
                                        for(int jj = m_rightt; jj >= m.c; jj--){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_rightt + 1 < n) m_rightt++;
                                    }
                                }
                            }
                        }
                        stoned_map[d][i][j] = 1; //몹의 그림자가 아니면 색칠
                    }
                    if(leftt - 1 >= 0) leftt--;
                    if(rightt + 1 < n) rightt++;
                }
            }
            else if(d == 2){ //좌
                leftt = sr - 1;
                rightt = sr + 1;
                for(int j = sc + dx[d]; j >= 0; j--){
                    for(int i = leftt; i <= rightt; i++){
                        if(stoned_map[d][i][j] == -1) continue; // 이미 그림자면 할거없음 패스
                        for(int idx=0; idx<mobs.size(); idx++){
                            mob m = mobs[idx];
                            if(m.is_die) continue;
                            if(m.r == i && m.c == j){ //몹과 영역이 만났을 경우
                                this_s++; //임시 돌이 될 몹 개수 증가
                                this_stoned.push_back(idx); //임시 돌이 될 몹 좌표 저장
                                stoned_map[d][m.r][m.c] = 1; //몹이 돌이 된것도 시야에 포함
                                if(m.r < sr){
                                    m_leftt = m.r - 1;
                                    for(int jj = m.c + dx[d]; jj >= 0; jj--){
                                        for(int ii = m_leftt; ii <= m.r; ii++){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_leftt - 1 >= 0) m_leftt--;
                                    }
                                }
                                else if(m.r == sr){
                                    for(int jj = m.c + dx[d]; jj >= 0; jj--){
                                        stoned_map[d][m.r][jj] = -1;
                                    }
                                }
                                else if(m.r > sr){
                                    m_rightt = m.r + 1;
                                    for(int jj = m.c + dx[d]; jj >= 0; jj--){
                                        for(int ii = m_rightt; ii >= m.r; ii--){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_rightt + 1 < n) m_rightt++;
                                    }
                                }
                            }
                        }
                        stoned_map[d][i][j] = 1; //몹의 그림자가 아니면 색칠
                    }
                    if(leftt - 1 >= 0) leftt--;
                    if(rightt + 1 < n) rightt++;
                }
            }
            else if(d == 3){ // 우 
                leftt = sr - 1;
                rightt = sr + 1;
                for(int j = sc + dx[d]; j < n; j++){
                    for(int i = leftt; i <= rightt; i++){
                        if(stoned_map[d][i][j] == -1) continue; // 이미 그림자면 할거없음 패스
                        for(int idx=0; idx<mobs.size(); idx++){
                            mob m = mobs[idx];
                            if(m.is_die) continue;
                            if(m.r == i && m.c == j){ //몹과 영역이 만났을 경우
                                this_s++; //임시 돌이 될 몹 개수 증가
                                this_stoned.push_back(idx); //임시 돌이 될 몹 좌표 저장
                                stoned_map[d][m.r][m.c] = 1; //몹이 돌이 된것도 시야에 포함
                                if(m.r < sr){
                                    m_leftt = m.r - 1;
                                    for(int jj = m.c + dx[d]; jj < n; jj++){
                                        for(int ii = m_leftt; ii <= m.r; ii++){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_leftt - 1 >= 0) m_leftt--;
                                    }
                                }
                                else if(m.r == sr){
                                    for(int jj = m.c + dx[d]; jj < n; jj++){
                                        stoned_map[d][m.r][jj] = -1;
                                    }
                                }
                                else if(m.r > sr){
                                    m_rightt = m.r + 1;
                                    for(int jj = m.c + dx[d]; jj < n; jj++){
                                        for(int ii = m_rightt; ii >= m.r; ii--){
                                            stoned_map[d][ii][jj] = -1;
                                        }
                                        if(m_rightt + 1 < n) m_rightt++;
                                    }
                                }
                            }
                        }
                        stoned_map[d][i][j] = 1; //몹의 그림자가 아니면 색칠
                    }
                    if(leftt - 1 >= 0) leftt--;
                    if(rightt + 1 < n) rightt++;
                }
            }
            
            if(best_s < this_s){ //돌이될 후보 업데이트
                look = d;
                best_s = this_s;
                best_stoned = this_stoned;
                best_map_idx = d;
            }
            
            //db_stoned_map();
        }
        //memcpy(real_stoned_map, stoned_map[best_map_idx], sizeof(stoned_map[best_map_idx]));
        for(int i=0; i<mobs.size(); i++){
            mobs[i].is_stone = 0;
        }
        for(int idx : best_stoned){
            mobs[idx].is_stone = 1;
        }
        cnt_s = best_s; //돌이 된 몹
        //3.전사들의 이동
        int m_ny, m_nx;
        for(mob& m : mobs){
            bool last_checker = false; //베스트가 현재 가만히 있는 선택인지
            for(int turn = 0; turn <2; turn++){
                if(m.r == sr && m.c == sc) continue; //이미 도달했으면 스탑
                int m_best_d = -1;
                int m_best_ret = 98765432; //한번만 초기화
                if(m.is_stone) continue; //돌됐으면 스킵
                if(m.is_die) continue;
                for(int d=0; d<4; d++){
                    if(turn == 0){ //첫번째 이동
                        m_ny = m.r + dy[d];
                        m_nx = m.c + dx[d];
                    }
                    else if(turn == 1) { //두번째 이동
                        m_ny = m.r + dy2[d];
                        m_nx = m.c + dx2[d];
                    }
                    if(m_ny < 0 || m_nx < 0 || m_ny >= n || m_nx >= n) continue;
                    fill(&visited[0][0], &visited[0][0] + 51*51, 0);
                    int m_ret = mob_bfs(m_ny, m_nx, sr, sc, turn);
                    if(m_ret < m_best_ret){
                        m_best_ret = m_ret; // ret 갱신
                        m_best_d = d; //방향 갱신
                        if(stoned_map[best_map_idx][m_ny][m_nx] == 1){ last_checker = true;}
                        else last_checker = false;
                    }
                    if(m_ret == m_best_ret){ //실제 움직임이 있는 방향으로 (거리를 줄이는 방향)
                        if(last_checker == true){
                            m_best_ret = m_ret; // ret 갱신
                            m_best_d = d; //방향 갱신
                        }
                    }
                }
                if(m_best_d != -1){ //공원까지의 도로가 존재하지않는 경우
                    if(turn == 0){
                        if(stoned_map[best_map_idx][m.r + dy[m_best_d]][m.c + dx[m_best_d]] == 1) continue; //이동할때 시야가 닿는곳이면 패스
                        m.r += dy[m_best_d];
                        m.c += dx[m_best_d];
                        cnt_d++;
                    }
                    else {
                        if(stoned_map[best_map_idx][m.r + dy2[m_best_d]][m.c + dx2[m_best_d]] == 1) continue; //이동할때 시야가 닿는곳이면 패스
                        m.r += dy2[m_best_d];
                        m.c += dx2[m_best_d];
                        cnt_d++;
                    }
                }
                
            }
        }
        
        // 4. 전사의 공격
        for(mob& m : mobs){
            if(m.is_die || m.is_stone) continue;
            if(m.r == sr && m.c == sc){
                cnt_a++; //공격한 몹
                m.is_die = true;
            }
            
        }
        
        cout << cnt_d << " " << cnt_s << " " << cnt_a << '\n';
    }
    return 0;
}
