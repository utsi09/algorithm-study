#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int n,q;
int adj[16][16];
int visited[16][16];

int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int sy[4] = {-1,0}; //아래, 왼쪽
int sx[4] = {0,-1};
int devide_cnt = 0;
int cnt;

struct Virus{
    int k,h,w,r,c;
    vector<pair<int,int>> removed; //제거된 r,c기준 좌표
    bool is_die; //전체가 죽었는지
};

vector<Virus> viruses;

void remove_virus(Virus& v){
    int r1 = v.r; int r2 = v.r + v.h - 1;
    int c1 = v.c; int c2 = v.c + v.w - 1;
    int i_plus, j_plus;
    for(int i=r1; i <= r2; i++){
        for(int j=c1; j<=c2; j++){
            for(pair<int,int> rm_pos : v.removed){ //제거된 바이러스는 스킵
                if(rm_pos.first == i_plus && rm_pos.second == j_plus) continue;
            }
            adj[i][j] = 0;
            j_plus++;
        }
        i_plus++;
    }
}

void put_virus(Virus& v){
    int r1 = v.r; int r2 = v.r + v.h - 1;
    int c1 = v.c; int c2 = v.c + v.w - 1;
    int i_plus, j_plus;
    for(int i=r1; i <= r2; i++){
        for(int j=c1; j<=c2; j++){
            for(pair<int,int> rm_pos : v.removed){ //제거된 바이러스는 스킵
                if(rm_pos.first == i_plus && rm_pos.second == j_plus) continue;
            }
            adj[i][j] = v.k;
            j_plus++;
        }
        i_plus++;
    }
}

void check_edit(Virus& v){
    int r1 = v.r; int r2 = v.r + v.h - 1;
    int c1 = v.c; int c2 = v.c + v.w - 1;
    for(int i=r1; i <= r2; i++){
        for(int j=c1; j<=c2; j++){
            if(adj[i][j] != v.k){
                v.removed.push_back(make_pair(i,j)); //제거되었으면 removed에 추가
            }
        }
    }

}

void DFS(int i, int j, int k){
    visited[i][j] = 1;
    for(int d=0; d<4; d++){
        int ny = i + dy[d];
        int nx = j + dx[d];
        if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
        if(visited[ny][nx] != 0) continue;
        if(adj[ny][nx] != k) continue;
        devide_cnt++;
        DFS(ny,nx,k);
    }
}

bool size_cmp(Virus& v1, Virus& v2){
    if(v1.w * v1.h - v1.removed.size() > v2.w * v2.h * v2.removed.size()) return true;
    return false;
}


//제일왼쪽 제일 위에서 떨어트리기 못떨어트리면 다음열
void reput_virus(Virus& v){
    //일단 r,c 0,0초기화
    int r1 = 0; int c1 = 0;
    int r2 = v.h - 1; int c2 = v.w - 1; 
    
    //일단 adj에 놔보기
    int relative_i, relative_j;
    int plus_i, plus_j;
    bool cant_put;
    while(1){
        if(plus_j >= n) return; // 열을 뚫으면 리턴
        cant_put = 0;
        // if(r1<0 || c1<0 || r2>=n || c2>=n) continue; //맵초과시 루프 해제
        int i;
        int j;
        bool skip_pos;
        relative_j = 0;
        relative_i = 0;
        for(i=r1 ; i<=r2; i++){ //위치는 확정, 하나씩 넣어보기
            for(j=c1; j<=c2; j++){
                skip_pos = false; //초기화
                for(pair<int,int> rm_pos : v.removed){
                    if(rm_pos.first == relative_i && rm_pos.second == relative_j){ //제거된 포즈는 스킵(상대위치기준)
                        skip_pos = true;
                        continue; 
                    } 
                }
                if(skip_pos){
                    relative_j++; //상대 열은 옮기고
                    continue; //제거했던거면 다음 요소로 스킵
                }
                if(i<0 || j<0 || i>=n || j>=n){ //오버플로우
                    relative_j++; //필요없긴한데 일단은
                    cant_put=1; 
                    continue;
                } 
                if(adj[i][j]!=0){ //요소있으면 스킵
                    relative_j++;
                    cant_put=1; 
                    continue;
                } 
                relative_j++;
            }
            if(cant_put) continue; //1개라도 안되면 검사할필요없음
            relative_i++;
        }
        if(!cant_put){ //들어갈수있으면
            v.r = r1;
            v.c = c1;
            put_virus(v);
            return; //함수 종료
        }
        plus_i++; //안되면 행 올리기
        r1 += plus_i; //r1자체를 올림
        r2 = r1 + v.h - 1; //r2도 올림
        if(r1 == n){ //천장 가면 다음 열로 이동
            plus_i = 0; //plus_i 초기화
            r1 = plus_i; //r1 바닥으로 초기화
            r2 = r1 + v.h - 1; //적용
            plus_j++; //열 1 증가
            c1 += plus_j; //c1에 더하기
            c2 = c1 + v.w - 1; //c2도 적용
        }
    }

}

bool k_cmp(Virus& v1, Virus& v2){
    if(v1.k < v2.k) return true; //k 오름차순
    return false;
}

int main(){
    cin >> n >> q;
    for(int k=1; k<=q; k++){
        int r1,c1,r2,c2; cin >> r1 >> c1 >> r2 >> c2;
        int h = r2 - r1;
        int w = c2 - c1;
        Virus v = {k,h,w,r1,c1};
        viruses.push_back(v);
        put_virus(v);
        //맵 수정 후
        for(Virus& tmp_v : viruses){ //박힌돌 검사
            if(tmp_v.is_die == true) continue;
            check_edit(v); //removed 반영 
            fill(&visited[0][0], &visited[0][0]+16*16, 0);
            devide_cnt = 0; //DFS로 순회한 인접 바이러스의 크기 
            int size = tmp_v.w * tmp_v.h - (tmp_v.removed.size());
            int i = tmp_v.r; int j = tmp_v.c;
            DFS(i, j, tmp_v.k); //분리 체크
            if(size != devide_cnt){ //분리되있으면 삭제
                remove_virus(tmp_v);
                tmp_v.is_die = true; 
            }
        }

        sort(viruses.begin(), viruses.end(), size_cmp); //사이즈 큰 순서로 바이러스 벡터 정렬
        bool can_reput;
        fill(&adj[0][0], &adj[0][0]+16*16, 0); //맵초기화
        for(Virus& tmp_v : viruses){
            if(tmp_v.is_die == true) continue; //죽었으면 패스
            reput_virus(tmp_v);
        }

        //K순서대로 벡터 IDX 정렬
        sort(viruses.begin(), viruses.end(), k_cmp); //k 오름차순

        //k만나면 viruses[k].size로 접근
        //DFS로 각 원점 넣고 K 만나면 그 K의 size를 내 바이러스 size와 곱하고 k저장해서 같은 k만나면 무시

        //페어 저장, (a.k, b.k)
        vector<pair<int,int>> adj_k;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                for(int d=0; d<4; d++){
                    int ny = i + dy[d];
                    int nx = j + dx[d];
                    if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
                    if(adj[ny][nx] == adj[i][j] || adj[ny][nx] == 0) continue; //나랑 같거나 0이면 스킵
                    adj_k.push_back(make_pair(adj[i][j], adj[ny][nx])); //K쌍을 넣기 순서바뀐거 여러개 같은거 여러개 가능
                }
            }
        }

        //first와 second를 작은게 앞으로
        for(pair<int,int>& tmp_k : adj_k){
            int tmp_k1 = tmp_k.first;
            int tmp_k2 = tmp_k.second;
            if(tmp_k2 > tmp_k1){ //뒤에꺼가 크면 순서 바꾸기
                tmp_k.first = tmp_k2;
                tmp_k.second = tmp_k1; 
            } 
        }
        //unique 함수
        unique(adj_k.begin(), adj_k.end()); //중복제거
        cnt = 0;
        //size 곱해서 더하기
        for(pair<int,int> tmp_k : adj_k){
            Virus v1 = viruses[tmp_k.first-1]; //k는 어차피 입력받은 순서 + 1
            Virus v2 = viruses[tmp_k.second-1];
            int v1_size = v1.w*v1.h - v1.removed.size();
            int v2_size = v2.w*v2.h - v2.removed.size();
            cnt += v1_size*v2_size;
        }
        cout << cnt << endl;
    }

    return 0;
}

/*
struct Virus{
    int k,h,w,r,c;
    vector<pair<int,int>> removed; //제거된 r,c기준 좌표
}


cin >> n, q
for(k=1 ~ q){
    cin >> r1 >> c1 >> r2 >> c2
    
    int h = r2 - r1;
    int w = c2 - c1;
    Virus v = {k,h,w,r1,c1};
    //이전값들 삭제

    맵 수정
    
    for(Virus : viruses){
        check_edit() //시작점 r,c 부터 넓이 높이만큼 순회하면서 k가 아닌게 있으면 좌표 removed 벡터에 push
    }

    //맵 확정후

    DFS로 분리됬는지 여부 후 true면 삭제 - 원점에서 돌앗을때 cnt가 최대 넓이보다 작으면 삭제

    virus 정렬 w*h 큰 순서



    for(auto : virus){
        모든 행 검사 for
            모든 열 검사 for 
                r,c 를 기준으로 바닥으로 납작하게 만들어서 1부터 n까지 충돌 검사하고 위에 인덱스 초과시 페일하고 다음행
    }

    //인접 판단
    for 모든 바이러스
    상하좌우로 납작하게 만듬
    nr nc 해서 check_adj 
    true면 넓이 곱함
    cnt +=

    cou<< cnt
    put_virus()

}

*/
