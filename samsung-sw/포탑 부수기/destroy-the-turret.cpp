#include <bits/stdc++.h>
using namespace std;
#define INF 98765432
int n,m,k;
int adj[11][11];
int visited[11][11];
int at_i, at_j; //공격자
int tg_i, tg_j; //타겟
int last_attack[11][11]; //최근 공격한 놈
int last_target[11][11]; //최근 공격당한 맵
int dy[4] = {0, 1, 0, -1}; //우하좌상
int dx[4] = {1, 0, -1, 0};
int lazer_map[11][11];
int cnt = 0;
int potton_dy[8] = {-1,1,0,0,-1,-1,1,1}; //상하좌우 좌상 우상 좌하 우하
int potton_dx[8] = {0,0,-1,1,-1,1,-1,1};
int strongest_potton = 0;
int t;

void db_last_adj(){
    cout << "----- last adj map -----\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << last_attack[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "----- map -----\n";
}
void db_map(){
    cout << "----- map -----\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << adj[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "----- map -----\n";
}
void db_visitedmap(){
    cout << "----- map -----\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << visited[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "----- map -----\n";
}
void db_lazermap(){
    cout << "----- map -----\n";
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << lazer_map[i][j] << " ";
        }
        cout << '\n';
    }
    cout << "----- map -----\n";
}

void select_target(){
    int highest_target = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i == at_i && j == at_j) continue; //공격자랑 같을수업음
            if(adj[i][j] == 0) continue; //부서진 포탑 스킵
            if(adj[i][j] > highest_target){
                tg_i = i;
                tg_j = j;
                highest_target = adj[i][j];
            }
            if(adj[i][j] == highest_target){
                if(last_attack[i][j] > last_attack[tg_i][tg_j]) continue; // 더 최근에 공격했으면 스킵
                else if(last_attack[i][j] < last_attack[tg_i][tg_j]){ //갱신
                    tg_i = i;
                    tg_j = j;
                }
                else{ //같으면
                    if(i+j > tg_i+tg_j) continue; //열과 행의 합
                    else if(i+j < tg_i+tg_j){
                        tg_i = i;
                        tg_j = j;
                    }
                    else{ //열과 행 합도 같으면
                        if(j > tg_j) continue; //열 비교
                        else {
                            tg_i = i;
                            tg_j = j;
                        }
                    }
                }
            }
        }
    }
    //cout << tg_i <<","<<tg_j << " : target! \n";
    //cout << adj[tg_i][tg_j] <<'\n';

}


void select_attacker(){
    int lowest_attack = INF;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(adj[i][j] == 0) continue; //부서진 포탑 스킵
            if(adj[i][j] < lowest_attack){
                at_i = i;
                at_j = j;
                lowest_attack = adj[i][j];
            }
            if(adj[i][j] == lowest_attack){
                if(last_attack[i][j] < last_attack[at_i][at_j]) continue; // best가 최근에 공격함
                else if(last_attack[i][j] > last_attack[at_i][at_j]){ //갱신
                    at_i = i;
                    at_j = j;
                }
                else{ //같으면
                    if(i+j < at_i+at_j) continue; //열과 행의 합
                    else if(i+j > at_i+at_j){
                        at_i = i;
                        at_j = j;
                    }
                    else{ //열과 행 합도 같으면
                        if(j < at_j) continue; //열 비교
                        else {
                            at_i = i;
                            at_j = j;
                        }
                    }
                }
            }
        }
    }
    adj[at_i][at_j] += (n+m);
    //cout << at_i <<","<<at_j << " : attacker! \n";
    //cout << adj[at_i][at_j] <<'\n';
}

void update_lastadj(){
    last_attack[at_i][at_j] = t;
    return;
}

pair<int,int> mirror_attack(int ny, int nx){
    if(nx < 0) nx = m-1;
    if(ny < 0) ny = n-1;
    if(nx >= m) nx = 0;
    if(ny >= n) ny = 0;
    return {ny, nx};
}

//거리 맵 생성
void bfs(){ 
    visited[tg_i][tg_j] = 1;
    queue<pair<int,int>> q;
    q.push({tg_i, tg_j});
    while(q.size()){
        int ii = q.front().first;
        int jj = q.front().second;
        q.pop();
        for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            tie(ny,nx) = mirror_attack(ny,nx); //반대쪽에서 나옴
            if(ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
            if(adj[ny][nx] == 0 || visited[ny][nx]) continue;
            visited[ny][nx] = visited[ii][jj] + 1;
            q.push({ny,nx});
        }
    }
}

void potton_attack(){
    adj[tg_i][tg_j] = max(0, adj[tg_i][tg_j] - (adj[at_i][at_j])); //타겟
    last_target[tg_i][tg_j] = t; //공격 대상
    for(int d=0; d<8; d++){
        int ny = tg_i + potton_dy[d];
        int nx = tg_j + potton_dx[d];
        tie(ny,nx) = mirror_attack(ny,nx); //반대쪽에서 나옴
        if(ny == at_i && nx == at_j) continue;
        adj[ny][nx] = max(0, adj[ny][nx] - (adj[at_i][at_j]) / 2); //지나가는 포탑
        last_target[ny][nx] = t; //공격 대상
    }    

}

bool lazer_attack(){
    fill(&visited[0][0], &visited[0][0]+11*11, 0);
    fill(&lazer_map[0][0], &lazer_map[0][0]+11*11, 0);
    lazer_map[at_i][at_j] = 1;
    bfs();
    if(!visited[at_i][at_j]) return false;
    //db_visitedmap();
    int ii = at_i;
    int jj = at_j;
    
    while(1){
        int shortest_dis = INF;
        int best_ny = -1;
        int best_nx = -1;
        for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            tie(ny,nx) = mirror_attack(ny,nx); //반대쪽에서 나옴
            if(ny < 0 || nx < 0 || ny >= n || nx >= m) continue;
            if(adj[ny][nx] == 0 || lazer_map[ny][nx]) continue;
            if(shortest_dis > visited[ny][nx]){
                shortest_dis = visited[ny][nx];
                best_ny = ny;
                best_nx = nx;
            }
        }
        if(best_ny != -1){
            lazer_map[best_ny][best_nx] = lazer_map[ii][jj] + 1;
            ii = best_ny;
            jj = best_nx;
            if(ii == tg_i && jj == tg_j){ //타겟 도달
                adj[tg_i][tg_j] = max(0, adj[tg_i][tg_j] - (adj[at_i][at_j])); //타겟
                last_target[tg_i][tg_j] = t; //공격 대상
                //cout << tg_i <<"," << tg_j << " : is attacked >> " << (adj[at_i][at_j]) << '\n';
                return true;
            }
            else {
                adj[ii][jj] = max(0, adj[ii][jj] - (adj[at_i][at_j]) / 2); //지나가는 포탑
                last_target[ii][jj] = t; //공격 대상
                //cout << ii <<"," << jj << " : is attacked >> " << (adj[at_i][at_j]) / 2 << '\n';
            }
        }
        
        if(best_ny == -1){ //경로없으면
            return false;
        }
    }
    
    return true;
}

void check_potton(){
    strongest_potton = 0;
    cnt = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(adj[i][j] > 0 && last_target[i][j] != t && last_attack[i][j] != t){//공격 x 부서지지않은 포탑중
                adj[i][j]++;
                //cout << i << "," << j << "heal \n";
            }
            if(adj[i][j] != 0){
                cnt++; //부서지지않은 포탑
            }
            strongest_potton = max(strongest_potton, adj[i][j]);
        }
    }

}


int main(){
    cin >> n >> m >> k;    
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> adj[i][j];
        }
    }

    fill(&last_attack[0][0], &last_attack[0][0]+11*11, 0); //0턴에 공격한 경험 있음
    fill(&last_target[0][0], &last_target[0][0]+11*11, 0); //0턴에 공격한 경험 있음
    for(t=1; t<=k; t++){
        // 1. 공격자 선정
        //db_last_adj();
        //db_map();

        select_attacker();
        select_target();
        
        update_lastadj(); //최근 공격자 맵 업데이트

        //2. 공격자의 공격
        if(!lazer_attack()){ //불가능시 포탄공격
            //db_map();
            //cout << "potton attack! \n";
            potton_attack();
            //db_map();
        }
        //3. 포탑 부서짐 - 자동
        // 4. 포탑 정비
        
        check_potton();
        // cout << " ----" << t << "----\n";
        // db_map();
        // db_last_adj();
        if(cnt == 1) break; //부서지지않은 포탑이 1개면 종료
    }
    
    cout << strongest_potton;

    return 0;
}