#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;
vector<int> tre_num; // : 유물번호 저장 
int adj[6][6];
int visited[6][6];

int tmp_adj[6][6]; // : 현재 순회중인  
int rotate_cp[6][6]; // : 현재 rotate 적용한 3x3 블록
int k, m;
int tmp[3][3];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
bool ender= false;

//
int best_num = 0; //가장 많이 찾은 보물수
int best_rot = 1e8; //가장 적은 회전수
int best_adj[6][6]; // : 가장 유물이 많이 발견된 복사맵
int best_row = 0;
int best_cul = 0;
vector<pair<int,int>> tre_pos;

int cnt=0;
int tmp_num = 0; //현재 찾은 보물수
int tmp_rot = 1e8; //현재 회전수
int tmp_row = 0;
int tmp_cul = 0;
vector<pair<int,int>> tmp_pos;
int ground_pos[6][6];
//
int pter=0;

void input(){
    cin >> k >> m;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cin >> adj[i][j];
        }
    }
    for(int num=0; num<m; num++){
        int tmp = 0;
        cin >> tmp;
        tre_num.push_back(tmp); //유물들 푸쉬
    }


}

void copy_map(){ //원본맵의 복사본 만들기
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            tmp_adj[i][j] = adj[i][j];
        }
    }

}

void debug_rotate_map(){
    cout << "----------tmp map--------\n";
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout << rotate_cp[i][j] << " ";
        }
        cout <<"\n";
    }

    cout << "----------tmp map--------\n";
    return;
}

void debug_tmp_adj_map(){
    cout << "----------tmp map--------\n";
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout << tmp_adj[i][j] << " ";
            
        }
        cout <<"\n";
    }

    cout << "----------tmp map--------\n";
    return;
}

void debug_refill_map(){
    cout << "----------debug_refill_map--------\n";
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout << adj[i][j] << " ";
        }
        cout <<"\n";
    }

    cout << "----------debug_refill_map--------\n";
    return;
}

void debug_tmp_map(){
    cout << "----------tmp map--------\n";
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout << tmp[i][j] << " ";
        }
        cout <<"\n";
    }

    cout << "----------tmp map--------\n";
    return;
}

void rotate(int or_i, int or_j, int turn){
    int rt_size = 3;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            int ii = or_i + i; //ori : 어디부터 시작할지 + 인덱스
            int jj = or_j + j;
            tmp[i][j] = tmp_adj[ii][jj]; //특정부분만 복사한 맵
        }
    }
    //debug_tmp_map();
    int tmptmp[3][3];
    while(turn >= 0){ // 0 1 2 
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                tmptmp[j][rt_size-i-1] = tmp[i][j]; //한번 회전
            }
        }
        for(int i=0; i<3; i++){ //다시 복사
            for(int j=0; j<3; j++){
                tmp[i][j] = tmptmp[i][j];
            }
        }
        turn--;
    }
    return;
}

bool check_overflow(int ny, int nx){
    if(ny<0 || nx<0 || ny>=5 || nx>=5) return true;
    return false;
}

void get_tre_pos(){
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(ground_pos[i][j]==1) tmp_pos.push_back({i,j});
        }
    }

}



void BFS(int i, int j, int tre){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    fill(&ground_pos[0][0], &ground_pos[0][0]+6*6, 0); //초기화
    ground_pos[i][j] = 1;
    q.push({i,j});
    int now_cnt = 1;
    while(q.size()){
        int tmp_i = q.front().first;
        int tmp_j = q.front().second;
        q.pop();
        for(int d=0; d<4; d++){
            int ny = tmp_i + dy[d];
            int nx = tmp_j + dx[d];
            if(check_overflow(ny,nx)) continue; //오버플로우
            if(visited[ny][nx] > 0) continue;
            if(tmp_adj[ny][nx] != tre) continue; //다른거면 스킵
            q.push({ny,nx});
            visited[ny][nx] = 1;
            now_cnt++;
            ground_pos[ny][nx] = 1;
            //tmp_num++; //3개 이상이면 이제 현재 보물수 증가  
            //cout << tre<< "tmpnum++\n";
        }
    }
    if(now_cnt>=3){
        get_tre_pos();
        tmp_num += now_cnt;
    } 
    return;
}

void BFS2(int i, int j, int tre){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    fill(&ground_pos[0][0], &ground_pos[0][0]+6*6, 0); //초기화
    ground_pos[i][j] = 1;
    q.push({i,j});
    int now_cnt = 1;
    bool checker = false;
    while(q.size()){
        int tmp_i = q.front().first;
        int tmp_j = q.front().second;
        q.pop();
        for(int d=0; d<4; d++){
            int ny = tmp_i + dy[d];
            int nx = tmp_j + dx[d];
            if(check_overflow(ny,nx)) continue; //오버플로우
            if(visited[ny][nx] > 0) continue;
            if(adj[ny][nx] != tre) continue; //다른거면 스킵
            q.push({ny,nx});
            visited[ny][nx] = 1;
            now_cnt++;
            ground_pos[ny][nx] = 1;
            // if(checker == true){
            //     cout << tre<< " << find\n";
            // }  
        }
    }
    if(now_cnt>=3){
        get_tre_pos();
        tmp_num += now_cnt;
    } 
    return;
}

void set_best_map(){
    for(int i=0; i<6; i++){
        for(int j=0; j<6; j++){
            best_adj[i][j] = tmp_adj[i][j];
        }
    }
}

void set_best(){
    best_num = tmp_num;
    best_rot = tmp_rot;
    best_row = tmp_row;
    best_cul = tmp_cul;
    set_best_map(); //best_map에 저장
    tre_pos.clear();
    tre_pos = tmp_pos; //좌표 벡터 넣기
    // cout << " ---------------\n";
    // for(auto p : tre_pos){
        
    //     cout << p.first << "," << p.second << ": trepos" <<endl;

    // }
    // cout << " --------" << best_num << "-------\n";
    return;
}

void get_best_adj(){
    fill(&visited[0][0], &visited[0][0]+6*6, 0); 

    tmp_num = 0;
    tmp_pos.clear(); //임시보물좌표 초기화
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(visited[i][j]!=0) continue; //방문했으면 스킵
            int tre = tmp_adj[i][j];
            BFS(i,j,tre);
            
        }
    }
    
    if(tmp_num > best_num){ //최대 보물수 갱신
        //debug_tmp_adj_map();
        set_best();
        //cout << tmp_num << "tmp num" << endl;
    }
    if(tmp_num == best_num){ //보물수 같을때
        if(tmp_rot < best_rot){ //회전수 더 적으면
            set_best();
        }
        if(tmp_rot == best_rot){
            if(best_cul > tmp_cul){
                set_best();
            }
            if(best_cul == tmp_cul){
                if(best_row > tmp_row){
                    set_best();
                }
            }
        } //회전수같으면 행열 작은거로
    }

}

void make_multi(){
    const int rt_size = 3; //3x3 사이즈
    for(int i=1 ; i<=rt_size; i++){
        for(int j=1 ; j<=rt_size; j++){ //9번 케이스
            //cout << i << "," << j << ": making tmp_map..." << endl;
            for(int turn=0; turn<3; turn++){ //
                fill(&tmp_adj[0][0], &tmp_adj[0][0]+6*6, 0); //tmp초기화하고 다시 복사
                copy_map(); //원본맵의 복사본 만들기  
                //cout << turn << endl;
                tmp_rot = turn+1;
                rotate(i-1,j-1,turn);
                tmp_row = i; tmp_cul = j;
                for(int ii=0; ii<3; ii++){
                    for(int jj=0; jj<3; jj++){
                        tmp_adj[ii+i-1][jj+j-1] = tmp[ii][jj];
                    }
                }
                //debug_tmp_adj_map();
                //여기서 tmp_adj 마다 검사
                get_best_adj();
            }
            
            //9번 케이스 종료
        }
    }
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            adj[i][j] = best_adj[i][j];
        }
    }
    //디버깅
    //debug_tmp_adj_map();
    //cout << tmp_num << "tmp num" << endl;
    return;
}


void pop_node(){
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            for(pair<int,int> p : tre_pos){ //보물위치면
                if(i==p.first && j == p.second){
                    //cout << i <<"," << j << " : tres" << endl;
                    adj[i][j] = 0; //0으로 채우기
                    cnt++;
                }
            }
        }
    }

}

void fill_adj(){
    //pop_node();
    for(int j=0; j<5; j++){
        for(int i=4; i>=0; i--){
            bool is_tre = false;
            if(adj[i][j] == 0){ //pop 되서 비어있으면 채우기
                adj[i][j] = tre_num[pter];
                pter++;
            }
        }
    }
    
}

void plus_tre(){
    tre_pos.clear();
    fill(&visited[0][0], &visited[0][0]+6*6, 0); 
    tmp_pos.clear();
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(visited[i][j]!=0) continue; //방문했으면 스킵
            int tre = adj[i][j];
            BFS2(i,j,tre);
        }
    }
    tre_pos = tmp_pos;
    pop_node(); //tres_pos와 겹치면 0으로
    fill_adj(); //0이면 순서대로 채우기
    
}

int main(){
    // 1. 입력
    input();
    
    for(int i=0; i<k; i++){

        best_num = 0;
        best_rot = 1e8;
        cnt = 0;         
        tre_pos.clear();

        make_multi(); 
        if(best_num == 0) break;
        // 2. 탐사 진행
        pop_node();
        //debug_tmp_adj_map();
        fill_adj(); //리필
        //cnt = tre_pos.size(); // 1회차 
       
        while(1){
            plus_tre(); //연쇄
            if(tre_pos.empty() == true) break;
            
            
            //debug_refill_map(); //디버깅
        }

        cout << cnt << " ";
    }

}

/*

2 20
7 6 7 6 7
6 7 6 7 6
6 7 1 5 4
7 6 3 2 1
5 4 3 2 7
3 2 3 5 2 4 6 1 3 2 5 6 2 1 5 6 7 1 2 3

*/
