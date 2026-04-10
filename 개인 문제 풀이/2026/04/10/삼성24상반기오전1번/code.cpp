#include <bits/stdc++.h>
using namespace std;

int k,m;
int adj[6][6];
int visited[6][6];
queue<int> tre_q;

struct rot_map{
    int tre_num; //adj에서 보물 개수
    int rotate; //회전수
    int row; 
    int col;
    int my_adj[6][6];
    //vector<pos> 대신 바로 0으로
};
rot_map best_map;
rot_map tmp_map;
int rotate_map[3][3];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};

bool no_tre = false;

//초기 입력 함수
void input(){
    cin >> k >> m;
    int tmp;
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cin >> tmp;
            adj[i][j] = tmp;
        }
    }
    for(int i=0; i<m; i++){
        cin >> tmp;
        tre_q.push(tmp);
    }
}

void init(){
    best_map.tre_num = 0;
    best_map.col = 5;
    best_map.row = 5;
    best_map.rotate = 4;
    fill(&best_map.my_adj[0][0], &best_map.my_adj[0][0]+6*6, 0); 
}

void debug_rot_map(){
    cout << "-----rot map ----\n";
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout << rotate_map[i][j] << " ";
        }
        cout<< "\n";
    }
    cout << "-----rot map ----\n";
}
void update_tmp(int row, int col, int rot){
    tmp_map.row = row;
    tmp_map.col = col;
    tmp_map.rotate = rot;
    tmp_map.tre_num = 0;
}

int tmp_rot[3][3];
void rotate(int i, int j, int rot){
    fill(&rotate_map[0][0], &rotate_map[0][0]+3*3, 0);
    fill(&tmp_rot[0][0], &tmp_rot[0][0]+3*3, 0);
    
    // i,j 부터 3x3 복사 -> 
    for(int r=0; r<3; r++){ //채우기
        for(int c=0; c<3; c++){
            rotate_map[r][c] = adj[r+i][c+j];
        }
    }
    int size_n = 3;
    for(int n = rot; n>0; n--){
        for(int r=0; r<3; r++){ //채우기
            for(int c=0; c<3; c++){
                tmp_rot[c][size_n-r-1] = rotate_map[r][c];
            }
        }
        memcpy(rotate_map, tmp_rot, sizeof(rotate_map)); //재회전해야하니까 
    }
    memcpy(tmp_map.my_adj, adj, sizeof(tmp_map.my_adj)); //원본맵 복사
    for(int r=0; r<3; r++){
        for(int c=0; c<3; c++){
            tmp_map.my_adj[r+i][c+j] = rotate_map[r][c]; //0~3에 있는거 원점 반영해서
            //cout << r+i << "," << c+j << "tmp map revise\n";
        }
    }
    //상태 업데이트
    update_tmp(i+1, j+1, rot); //행, 열 , 회전수 넣기, 보물수 0초기화
}


void debug_tmp_map(){
    cout << "-----debug_tmp_map----\n";
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            cout << tmp_map.my_adj[i][j] << " ";
        }
        cout<< "\n";
    }
    cout << "-----debug_tmp_map ----\n";

}

void BFS(int i, int j, bool is_real){
    queue<pair<int,int>> q;
    q.push({i,j});
    visited[i][j] = 1;
    vector<pair<int,int>> pop_pos;
    pop_pos.clear(); //초기화
    pop_pos.push_back({i,j});
    int now_cnt = 1;
    while(q.size()){
        int ii = q.front().first; int jj = q.front().second;
        q.pop();
        for(int d=0; d<4; d++){
            int ny = ii + dy[d];
            int nx = jj + dx[d];
            if(ny<0 || nx<0 || ny>=5 || nx>=5) continue;
            if(visited[ny][nx]!=0) continue;
            if(tmp_map.my_adj[i][j] != tmp_map.my_adj[ny][nx]) continue; //시작 점이랑 기호다르면 
            now_cnt++;
            visited[ny][nx] = 1;
            q.push({ny,nx});
            pop_pos.push_back({ny,nx});
        }
    }
    if(now_cnt >= 3){ // 3개 이상이면 tmp 정보 업데이트
        if(is_real == true){
            for(auto p : pop_pos){ // 시뮬아니면 바로 팝
                //cout << "pop" << endl;
                tmp_map.my_adj[p.first][p.second] = 0; //0으로 팝
            }
        }
        tmp_map.tre_num += now_cnt; //보물개수 증가
    }
}

void update_best(){
    best_map = tmp_map;
}

void simulate(){ //tmp map 시뮬레이션 - 27번
    fill(&visited[0][0], &visited[0][0]+6*6, 0);
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(visited[i][j] > 0) continue;
            BFS(i,j,0); //0이면 시뮬레이션
        }
    }
    //best 와 비교후 업데이트
    if(tmp_map.tre_num > best_map.tre_num){
        update_best(); //best 업데이트
    }
    if(tmp_map.tre_num == best_map.tre_num){
        if(tmp_map.rotate < best_map.rotate){
            update_best();
        }
        if(tmp_map.rotate == best_map.rotate){
            if(tmp_map.col < best_map.col){
                update_best();
            }
            if(tmp_map.col == best_map.col){
                if(tmp_map.row < best_map.row){
                    update_best();
                }
            }
        }
    }
    return;
}

void explore(){
    for(int i=1; i<=3; i++){
        for(int j=1; j<=3; j++){
            for(int rot=1; rot<=3; rot++){
                rotate(i-1,j-1,rot);
                //여기서 시뮬레이션 돌리기
                simulate(); 
            }
            
        }
    }
    if(best_map.tre_num == 0) no_tre = true;
    return;
}

void tmp_init(bool is_first){
    tmp_map.col = 0;
    tmp_map.row = 0;
    tmp_map.rotate = 0;
    tmp_map.tre_num = 0;
    if(is_first){
        memcpy(tmp_map.my_adj, adj, sizeof(tmp_map.my_adj)); //adj로 tmp 갱신
    }
    else{
        memcpy(tmp_map.my_adj, best_map.my_adj, sizeof(tmp_map.my_adj)); //best_adj로 tmp 갱신
    }
}

void pop_map(){
    fill(&visited[0][0], &visited[0][0]+6*6, 0);
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            if(visited[i][j] > 0) continue;
            BFS(i,j,1); //1이면 바로 팝
        }
    }

}

void fill_map(){
    for(int c=0; c<5; c++){
        for(int r=4; r>=0; r--){
            if(tmp_map.my_adj[r][c] == 0){
                int tre = tre_q.front(); tre_q.pop();
                tmp_map.my_adj[r][c] = tre;
            }
        }
    }
}

int main(){
    input();
    for(int turn = 0; turn < k; turn++){ //k만큼 탐사 반복
        init(); //best 초기화
        tmp_init(true); //tre 초기화
        //탐사진행
        explore();
        if(no_tre == true) break;
        // 베스트맵으로 진행 2. 유물획득
        memcpy(tmp_map.my_adj, best_map.my_adj, sizeof(tmp_map.my_adj)); //best를 템프로
        best_map.tre_num = 0;
        while(1){ //맵은 확정, 계속 pop하기         
            tmp_map.tre_num = 0;
            pop_map(); //0 처리
            if(tmp_map.tre_num == 0) break;
            best_map.tre_num += tmp_map.tre_num; //보물개수 갱신
            fill_map();
        }
        
        cout << best_map.tre_num << " "; //누적
        memcpy(adj, tmp_map.my_adj, sizeof(adj)); //원본맵 변경
    }

    return 0;
}

