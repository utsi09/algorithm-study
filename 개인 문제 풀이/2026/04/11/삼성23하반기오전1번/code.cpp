#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;
int l, n, q;
const int m_size = 41;
int adj[m_size][m_size];
int w_map[m_size][m_size];
int cnt = 0;
struct Warrior{
    int r, c, h, w, k;
    int now_k = k;
    bool is_die = false;
    int idx;
};
vector<int> moved_w;
vector<Warrior> warriors;
vector<pair<int,int>> call;
pair<int,int> tmp_call;
Warrior tmp_w;
int tmp_direction;
int dy[4] ={-1, 0, 1, 0};
int dx[4] ={0, 1, 0, -1};

void input(){
    cin >> l >> n >> q;
    for(int i=0; i<l; i++){ //맵 입력
        for(int j=0; j<l; j++){
            int tmp; cin >> tmp;
            adj[i][j] = tmp;
        }
    }
    for(int i=0; i<n; i++){ //기사 입력
        Warrior tmp_w;
        int r,c,h,w,k; cin >> r >> c >> h >> w >> k;
        tmp_w.r = r-1; tmp_w.c = c-1; tmp_w.h = h; tmp_w.w = w; tmp_w.k = k;
        tmp_w.now_k = k;
        tmp_w.idx = i+1; //idx는 1부터
        warriors.push_back(tmp_w);
    }
    for(int i=0; i<q; i++){ //명령 입력
        int tmp1, tmp2; cin >> tmp1 >> tmp2;
        call.push_back({tmp1,tmp2}); //명령 벡터에 입력
    }
    return;
}

void init_wmap(){ //명령 받은 기사 제외한 맵
    fill(&w_map[0][0], &w_map[0][0]+m_size*m_size, 0); //워리어맵 초기화
    for(int i=0; i<warriors.size(); i++){
        if(warriors[i].now_k <= 0) continue; //죽었으면 안그림
        if(i+1 == tmp_w.idx) continue; //명령받은 기사면 안그림
        int r1, c1, h, w, idx;
        r1 = warriors[i].r; c1 = warriors[i].c; h = warriors[i].h; w = warriors[i].w;
        int r2 = r1 + h - 1; int c2 = c1 + w - 1;
        for(int r=r1; r<=r2; r++){
            for(int c=c1; c<=c2; c++){
                w_map[r][c] = warriors[i].idx;
            }
        }
    }
}

void db_w_map(){
    cout <<"------w_map-------\n";
    for(int i=0; i<l ; i++){
        for(int j=0; j<l; j++){
            cout << setw(2)<< w_map[i][j] << " ";
        }
        cout <<"\n";
    }
    cout <<"------w_map-------\n";
}

// bool can_move(int ny, int nx){
    
// }
void attacked(int idx){
    for(int i=0; i<l; i++){
        for(int j=0; j<l; j++){
            if(adj[i][j] != 1) continue; //함정없으면 스킵
            //if(w_map[i][j] == 0) continue; //전사없으면스킵
            if(w_map[i][j] == idx){ //받은 idx면
                warriors[idx-1].now_k--; //피 1 마이너스
                //cout << idx << " : attacked!! pos :" << i <<","<<j<<"\n";
            }
            
        }
    }
}

bool suquence_move(int idx){
    int r1, c1, r2, c2;
    r1 = warriors[idx-1].r;
    c1 = warriors[idx-1].c;
    r2 = r1 + warriors[idx-1].h - 1;
    c2 = c1 + warriors[idx-1].w - 1;
    if(tmp_direction==0) r2 = r1; //납작하게 만들기
    if(tmp_direction==1) c1 = c2;
    if(tmp_direction==2) r1 = r2;
    if(tmp_direction==3) c2 = c1;
    //cout << r1 << c1 << r2 << c2 << endl;
    for(int i=r1; i<=r2; i++){
        for(int j=c1; j<=c2; j++){
            int ny = i + dy[tmp_direction];
            int nx = j + dx[tmp_direction];
            if(ny<0 || nx<0 || ny>=l || nx>=l) return false; //overflow
            if(adj[ny][nx]==2) return false; //벽이면 false
            if(w_map[ny][nx]>0){ //전사가 있으면
                if(!suquence_move(w_map[ny][nx])) return false;//그 전사로 재귀함수 실패시 false
            }
        }
    }
    //r,c 이동시키기
    //cout << "before move : " <<  warriors[idx-1].r << warriors[idx-1].c << endl;
    
    //cout << "after move : " <<  warriors[idx-1].r << warriors[idx-1].c << endl;
    //w_map 다시그리기
    moved_w.push_back(idx);
    return true; //이동할것들 푸시만 하고 true
}

void cnt_check(){
    for(Warrior w : warriors){
        if(w.now_k <= 0) continue;
        int tmp_cnt = w.k - w.now_k;
        //cout << w.k << ":full" << w.now_k << endl;
        //cout << w.idx << " : " << tmp_cnt << endl;
        cnt += tmp_cnt;
    }

}
//t4 데미지를 더 받았어야 했다.

void real_move(){
    for(int idx : moved_w){
        warriors[idx-1].r = warriors[idx-1].r + dy[tmp_direction];
        warriors[idx-1].c = warriors[idx-1].c + dx[tmp_direction];
    }

}

int main(){
    input();

    for(int i=0; i<call.size(); i++){
        moved_w.clear();
        fill(&w_map[0][0], &w_map[0][0]+m_size*m_size, 0); //워리어맵 초기화
        tmp_call = call[i]; // i 번째 
        tmp_w = warriors[tmp_call.first-1]; //명령받은 기사
        if(tmp_w.now_k <= 0) continue; //죽었으면 스킵
        tmp_direction = tmp_call.second; //명령받은 방향
        init_wmap();

        if(suquence_move(tmp_w.idx) == false) {
            moved_w.clear(); 
            continue; //이동 못하면 
        }
        sort(moved_w.begin(),moved_w.end());
        moved_w.erase(unique(moved_w.begin(),moved_w.end()),moved_w.end());
        real_move();
        init_wmap();
        for(int move_idx : moved_w){
            attacked(move_idx);
        }
        
        //db_w_map();
    }

    cnt_check();
    cout << cnt;
    return 0;
}
