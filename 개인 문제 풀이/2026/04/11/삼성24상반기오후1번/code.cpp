#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <iomanip>
using namespace std;

const int m_size = 71;
int adj[m_size][m_size];
int visited[m_size][m_size];

int r,c,k;

int dy[4] = {-1,0,1,0};
int dx[4] = {0,1,0,-1};
bool is_full = false;
int cnt = 0;

struct Robot{
    pair<int,int> pos; //절대 좌표
    int direction = 0;
    bool is_pop = false;
    int score = 0;
    int idx = 0;
};

vector<Robot> robot_q;
Robot tmp_rb;

//초기 입력
void input(){
    cin >> r >> c >> k;
    for(int i=1; i<=k; i++){
        int jj, direction;
        cin >> jj >> direction;
        Robot rb;
        rb.pos.first = -2;
        rb.pos.second = jj-1;
        rb.direction = direction;
        rb.idx = i;
        robot_q.push_back(rb);
    }
}

bool down(int i, int j){
    for(int d=0; d<4; d++){
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(nx<0 || ny>=r || nx>=c) return false; //ny 가 0보다 작은건 허용
        if(adj[ny][nx] != 0 && ny>=0){
            return false;
            //cout << "down robot alive\n";    
        }
    }
    return true;
}

bool left(int i, int j){
    for(int d=0; d<4; d++){ //왼쪽 1칸 4방향 검사
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(nx<0 || ny>=r || nx>=c) return false; //ny 가 0보다 작은건 허용
        if(ny >= 0 && adj[ny][nx] != 0) return false; //로봇 있으면
    }
    if(down(i+1,j)) return true; //아래 한칸 내려간거 검사
    else return false;
}

bool right(int i, int j){
    for(int d=0; d<4; d++){ //오른쪽 1칸 4방향 검사
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(nx<0 || ny>=r || nx>=c) return false; //ny 가 0보다 작은건 허용
        if(ny >= 0 && adj[ny][nx] != 0) return false; //로봇 있으면
    }
    if(down(i+1,j)) return true; //아래 한칸 내려간거 검사
    else return false;
}

bool draw_rb(){
    int i = tmp_rb.pos.first;
    int j = tmp_rb.pos.second;
    if(i<1) return false;
    adj[i][j] = tmp_rb.idx;
    //cout << "draw" << endl;  
    for(int d =0; d<4; d++){
        if(i+dy[d] < 0){
            //cout << "head cut" << endl; 
            return false;
        }
        if(d == tmp_rb.direction) adj[i+dy[d]][j+dx[d]] = -(tmp_rb.idx);
        else adj[i+dy[d]][j+dx[d]] = tmp_rb.idx;
    }
    return true;
}

void move(){
    while(1){
        int tmp_i = tmp_rb.pos.first;
        int tmp_j = tmp_rb.pos.second;
        //cout << tmp_i << "," << tmp_j << endl;
        if(down(tmp_i+1, tmp_j)){ //true 반환시
            tmp_rb.pos.first += 1;
            continue;
        }
        if(left(tmp_i, tmp_j-1)){
            tmp_rb.pos.first += 1;
            tmp_rb.pos.second -= 1;
            tmp_rb.direction -= 1;
            //cout << tmp_rb.direction << "- direc\n";
            if(tmp_rb.direction < 0 ) tmp_rb.direction = 3;
            continue;
        }
        if(right(tmp_i, tmp_j+1)){
            tmp_rb.pos.first += 1;
            tmp_rb.pos.second += 1;
            tmp_rb.direction += 1;
            //cout << tmp_rb.direction << "+ direc\n";
            if(tmp_rb.direction >= 4 ) tmp_rb.direction = 0;
            continue;
        }
        break; //다 안되면 멈추기
    }
    //cout << "go draw\n";
    if(!draw_rb()) is_full = true;
}

void db_adj(){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            cout << setw(2) << adj[i][j] << " ";
        }
        cout << "\n";
    }
}

//단순히 visited 처리, score와 탐색 노드의 행 비교
void BFS(int i, int j){ 
    tmp_rb.score = max(i+1,tmp_rb.score); //행이 큰걸로 갱신
    queue<pair<int,int>> q;
    q.push({i,j});
    visited[i][j] = 1;
    while(q.size()){
        int tmp_i = q.front().first;
        int tmp_j = q.front().second;
        q.pop();
        for(int d =0; d<4; d++){
            int ny = tmp_i + dy[d];
            int nx = tmp_j + dx[d];
            if(ny<0 || nx<0 || ny>=r || nx>=c) continue;
            if(visited[ny][nx] != 0) continue;
            if(adj[ny][nx] == 0) continue;
            if(abs(adj[tmp_i][tmp_j]) == abs(adj[ny][nx]) || adj[tmp_i][tmp_j] < 0){ //양수 -> 음수
                //cout << adj[ny][nx] <<": visit!!\n";
                q.push({ny,nx});
                visited[ny][nx] = 1;
                tmp_rb.score = max(ny+1,tmp_rb.score);
            }
        }
    }
}


void move_score(){
    fill(&visited[0][0], &visited[0][0]+m_size*m_size, 0);
    int i = tmp_rb.pos.first;
    int j = tmp_rb.pos.second;
    BFS(i,j);
    
    return;
}

void get_score(){
    //가장 아래 다리 점수
    tmp_rb.score = tmp_rb.pos.first + 2;
    //cout << tmp_rb.score;
    move_score();

    //bfs로 출구 연결돼있으면 타고 가장 아래로

}

int main(){
    input();
    fill(&adj[0][0], &adj[0][0]+m_size*m_size, 0);
    for(int t=0; t < robot_q.size(); t++){
        is_full = false;
        tmp_rb = robot_q[t]; //현재 로봇 변경
        //로봇이동
        move();
        //db_adj();
        if(is_full == true){
            fill(&adj[0][0], &adj[0][0]+m_size*m_size,0); //맵 클리어
            continue;
        }
        
        //정령이동(점수)
        get_score();
        cnt += tmp_rb.score;


    }
    cout << cnt << endl;
    return 0;
}
