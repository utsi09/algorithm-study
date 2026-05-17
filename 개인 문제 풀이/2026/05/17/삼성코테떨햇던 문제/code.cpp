#include <bits/stdc++.h> 
using namespace std;
int n, m, k;
int adj[21][21];


struct turtle{
    int i; int j; 
    bool is_die = false;
    int arrive_time=-1;
};
vector<turtle> turtles;

struct fire
{
    int i; int j; int p; int now_p=0;
    bool max_boom = false;
    bool now_boom = false;
};
vector<fire> fires(k);
int visited[21][21];
int fire_map[21][21];
int ii, jj;
int dy[4] = {0, 1, 0, -1};
int dx[4] = {1, 0 , -1, 0}; //우하좌상

int bfs(int i, int j){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i, j});
    while(q.size()){
        tie(ii,jj) = q.front(); q.pop();
        if(ii==n-1 && jj==n-1){ //탈출기저사례
            break;
        }
        for(int d=0; d<4; d++){
            int ny = ii + dy[d]; int nx = jj + dx[d];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(visited[ny][nx]) continue;
            if(adj[ny][nx]) continue; //산호초
            bool is_tutle = false;
            for(int i=0; i<m; i++){
                if(ny == turtles[i].i && nx == turtles[i].j) {is_tutle = true; continue;}
            }
            if(is_tutle) continue;
            visited[ny][nx] = visited[ii][jj] + 1;
            q.push({ny,nx});
        }
    }
    return visited[n-1][n-1];
}

int move(int arrive_time){
    for(turtle& t : turtles){ //각 거북이마다
        if(t.is_die == true) continue;
        if(t.arrive_time != -1) continue; //도착시 계산 제외
        int best_ret=9876543;
        pair<int,int> best_pos = {t.i, t.j}; //초기값으로 초기화
        for(int dd=0; dd<4; dd++){
            fill(&visited[0][0], &visited[0][0]+21*21, 0); //4방향마다 초기화
            int ny = t.i + dy[dd]; int nx = t.j + dx[dd];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(adj[ny][nx]) continue; //산호초
            bool is_tutle = false;
            for(int i=0; i<m; i++){
                if(ny == turtles[i].i && nx == turtles[i].j) {is_tutle = true; continue;}
            }
            if(is_tutle) continue;
            int ret = 0;
            ret = bfs(ny,nx);
            //cout << ret << endl;
            if(ret == 0) continue;
            else if(ret < best_ret){ //갱신
                best_pos.first = ny; best_pos.second = nx;
                best_ret = ret;
            }
        }
        t.i = best_pos.first; t.j = best_pos.second; //이동
        if(t.i == n-1 && t.j == n-1){
            t.arrive_time = arrive_time;
            t.i = -1; t.j = -1;
        }
        //cout << "move to :" << t.i <<"," <<t.j <<"\n";
    }

    return 0;
}

void db_map(){
    cout << "---------\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            bool ob = false;
            for(turtle& t : turtles){
                if(t.i == i && t.j == j) {ob = true; cout << "T"; continue;}
            }
            for(fire f : fires){
                if(f.i == i && f.j == j) {ob = true; cout << "F"; continue;}
            }
            
            if(!ob) cout << adj[i][j];
            cout << " ";
        }
        cout << "\n";
    }
    cout << "---------\n";
    return;
}

void db_fmap(){
    cout << "---------\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << fire_map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "---------\n";
    return;
}


void fire_up(){
    for(fire& f : fires){
        f.now_p += 10;
    }
}

//fire를 받아서 firemap에 불 번지게
void transition(fire& f){
    f.now_boom = true;
    //cout << f.i << "," << f.j << " : boom!\n";
    fire_map[f.i][f.j] += f.p;
    //cout << fire_map[f.i][f.j] << endl;
    for(int d=0; d<4; d++){
        int energy = f.p / 2;
        int i = f.i; int j = f.j;
        while(1){
            int ny = i + dy[d];
            int nx = j + dx[d];
            if(ny<0 || nx<0 || ny>=n || nx>=n) break;
            if(adj[ny][nx]) break;
            if(energy == 0) break;
            fire_map[ny][nx] += energy;
            energy = energy / 2;
            i = ny; j = nx;
        }
    }
    f.now_p = 0;
    for(int ff=0; ff<k; ff++){ //연쇄검사
        if(f.i == fires[ff].i && f.j == fires[ff].j || fires[ff].now_boom == true) continue;
        if(fire_map[fires[ff].i][fires[ff].j] + fires[ff].now_p >= fires[ff].p){
            transition(fires[ff]);
        }
    }
    return;
}

void boom(){
    fill(&fire_map[0][0], &fire_map[0][0]+21*21, 0);
    for(int f=0; f<k; f++){
        fires[f].now_boom = false;
        if(fires[f].now_p >= fires[f].p){ //열기 전파
            transition(fires[f]); 
        }
    }
}

void die_check(){
    for(turtle& t : turtles){
        if(fire_map[t.i][t.j] >= 20) t.is_die = true;
    }

}

int main(){
    cin >> n >> m >> k;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> adj[i][j];
        }
    }
    for(int i=0; i<m; i++){
        int tmpi; int tmpj; cin >> tmpi >> tmpj;
        turtle tmp_t;
        tmp_t.i = tmpi; tmp_t.j = tmpj;
        turtles.push_back(tmp_t);
    }
     //cout << "input\n";
    for(int i=0; i<k; i++){
        int tmpi; int tmpj; int tmpp; cin >> tmpi >> tmpj >> tmpp;
        fire f; f.i = tmpi; f.j=tmpj; f.p = tmpp;
        fires.push_back(f);
    }
    //cout << "input\n";
    //db_map();
    for(int i=1; i<=100; i++){
        //cout << "----" << i << " : turn start\n";
        move(i); //거북이 이동
        fire_up(); //화산 10 증가
        boom(); //화산 터짐
        //db_fmap();
        die_check(); //화석 체크
        //db_map();
        //cout << "----" << i << " : turn end\n";
    }
    for(int t=0; t<m; t++){
        cout << turtles[t].arrive_time <<'\n';
    }
    return 0;
}
