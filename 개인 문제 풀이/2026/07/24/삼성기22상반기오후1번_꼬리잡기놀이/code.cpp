#include <bits/stdc++.h>
using namespace std;
int n,m,k;
int adj[21][21];
vector<vector<pair<int,int>>> teams;
int dy[4] = {-1,1,0,0}; //상하좌우
int dx[4] = {0,0,-1,1};
int visited[21][21];
int score = 0;


// 팀에 누구있는지 디버깅
void db_teams(){
    for(auto& team : teams){
        cout <<"--team--\n";
        for(auto& p : team){
            cout << p.first <<"," << p.second << "||";
        }
        cout << "\n";
    }

}

void db_map(){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << adj[i][j] <<" ";
        }
        cout <<'\n';
    }
}

//team 머리부터 꼬리까지 좌표 저장
void init(){
    for(auto& team : teams){
        memset(visited,0,sizeof(visited));
        int ii = team[0].first;
        int jj = team[0].second;
        visited[ii][jj] = 1;
        while(1){
            if(adj[ii][jj] == 3){
                adj[ii][jj] = 1;
                break;
            }
            int here = adj[ii][jj];
            adj[ii][jj] = 1; //이제 맵에서는 사람 여부만 확인
            for(int dd=0; dd<4; dd++){
                int ny = ii + dy[dd];
                int nx = jj + dx[dd];
                if(ny<0 || nx<0 || ny>=n || nx>=n ||visited[ny][nx]) continue;
                if(adj[ny][nx] != 0 && !(adj[ny][nx] > here + 1) ){ //팀에 넣을 곳
                    visited[ny][nx] = 1;
                    team.push_back({ny,nx});
                    ii = ny;
                    jj = nx;
                }
            }
        }
        
    }

}

pair<int,int> find_space(int sr, int sc, int no_r, int no_c){
    for(int dd=0; dd<4; dd++){
        int ny = sr + dy[dd];
        int nx = sc + dx[dd];
        if(ny<0 || nx<0 || ny>=n || nx>=n || adj[ny][nx] == 0) continue;
        if(ny == no_r && nx == no_c) continue;
        return {ny,nx};
    }
}


void move_team(){
    for(auto& team : teams){ 
        auto next = find_space(team[0].first, team[0].second, team[1].first, team[1].second);
        //맵에서 삭제
        for(const auto& p : team){
            adj[p.first][p.second] = 4;
        }
        //teams벡터 삽입
        team.insert(team.begin(), next);
        team.erase(team.end()-1);

        //맵에 다시 그리기
        for(const auto& p : team){
            adj[p.first][p.second] = 1;
        }
    }

}

void move_ball(int t){
    int table = (t / n) % 4;
    //cout << "table : " << table <<'\n';
    pair<int,int> start, ball_direction;
    if(table == 0){
        start = {t % n, 0};
        ball_direction = {0, 1};
    }
    else if(table == 1){
        start = {n-1, t % n};
        ball_direction = {-1, 0};
    }
    else if(table == 2){
        start = {n-1 - (t%n), n-1};
        ball_direction = {0, -1};
    }
    else{
        start = {0, n-1 - (t%n)};
        ball_direction = {1, 0};
    }

    int ii = start.first;
    int jj = start.second;
    while(1){
        if(ii<0 || jj<0 || ii>=n || jj>=n) break;
        if(adj[ii][jj] == 1){ //사람 만나면
            pair<int,int> target = {ii,jj};
            for(auto& team : teams){
                auto it = find(team.begin(), team.end(), target);
                if(it != team.end()){
                    int index = distance(team.begin(), it) + 1;
                    score += pow(index, 2);
                    // 방향 전환
                    reverse(team.begin(), team.end());
                }
            }
            break;
        }
        ii += ball_direction.first;
        jj += ball_direction.second;
    }
    
}

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
            if(adj[i][j] == 1){
                vector<pair<int,int>> v;
                v.push_back({i,j});
                teams.push_back(v); //머리만 팀 목록에 넣기
            }
        }
    }

    init();
    //db_map();
    for(int t=0; t<k; t++){
        //1.각 팀 이동
        //cout <<"--- turn :" << t <<"---\n";
        move_team();
        //db_teams();
        //db_map();
        move_ball(t);
        //db_teams();
        //db_map();
    }
    cout << score;
    return 0;
}
