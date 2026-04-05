#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;
int n,m;

vector<vector<int>> adj; //맵
int dy[3] = {1, 0, 0}; // 아래 , 왼쪽, 오른쪽
int dx[3] = {0, -1, 1};

struct Box{
    int k, h, w, r ,c;
    bool is_remove;
};
vector<Box> boxes;

bool can_move(int h, int w, int r, int c, int d){
    int r1 = r; int r2 = r+h-1;
    int c1 = c; int c2 = c+w-1;
    if(d==0) r1 = r2;
    if(d==1) c2 = c1;
    if(d==2) c1 = c2;
    for(int i = r1; i <= r2; i++){
        for(int j = c1; j<=c2; j++){
            if(i<0 || j<0 || i>=n || j>=n) return false; //오버플로우
            if(adj[i][j] != 0) return false;
        }
    }
    // cout << "can move!!! complete" << endl;
    return true;
}

pair<int,int> move_box(int h, int w, int r, int c, int d){
    int r1 = r;
    int c1 = c;

    while(1){
        int nr = r1 + dy[d];
        int nc = c1 + dx[d];
        if(can_move(h,w,nr,nc,d)){
            r1 = nr; c1 = nc;
        }
        else{
            break;
        }
    }
    return make_pair(r1,c1);
}

void put_box(Box& b){
    for(int i = b.r; i <= b.r+b.h-1 ; i++){
        for(int j = b.c; j <= b.c+b.w-1 ; j++){
            adj[i][j] = b.k;
        }
    }
}

void remove_box(Box& b){
    for(int i = b.r; i <= b.r+b.h-1 ; i++){
        for(int j = b.c; j <= b.c+b.w-1 ; j++){
            adj[i][j] = 0;
        }
    }
}

bool cmp_k(Box& b1, Box& b2){
    if(b1.k < b2.k) return true;
    return false;
}

bool cmp_floor(Box& b1, Box& b2){
    if(b1.r+b1.h -1 > b2.r+b2.h-1) return true;
    return false; 
}

int main(){
    cin >> n >> m;
    adj.assign(n,vector<int>(n,0));
    //boxes.resize();

    //초기 put
    for(int num = 0; num < m; num++){
        int k, h, w, c; cin >> k >> h >> w >> c;
        int r1 = 0; int c1 = c-1;
        pair<int,int> tmp_pair = move_box(h,w,r1,c1,0);
        Box b{k,h,w,tmp_pair.first, tmp_pair.second, false};
        boxes.push_back(b);
        put_box(boxes.back());
    }
    

    // for(int i=0;i<n;i++){
    //     for(int j=0; j<n;j++){
    //         cout << setw(2) << adj[i][j];
    //     }
    //     cout << "\n";
    // }

    sort(boxes.begin(), boxes.end(), cmp_k); //택배번호순 정렬
    // for(Box i : boxes){
    //     cout << i.k << " ";
    // }


    for(int turn=0; turn < m; turn++){
        bool is_Left = turn % 2 == 0;

        //좌우 빼기
        for(Box& tmp_b : boxes){
            //cout << tmp_b.k << endl;
            if(tmp_b.is_remove){
                //cout << tmp_b.k << "already done" << endl;
                continue;
            }
            remove_box(tmp_b);
            pair<int,int> tmp_pair = move_box(tmp_b.h, tmp_b.w, tmp_b.r, tmp_b.c, is_Left ? 1 : 2);
            bool can_exit = is_Left ? (tmp_pair.second == 0) : (tmp_pair.second + tmp_b.w - 1 == n-1);
            //cout << can_exit << " :can_exit" <<endl;
            if(can_exit){
                cout << tmp_b.k <<endl;
                tmp_b.is_remove = true;
                //cout << tmp_b.is_remove << "remove edit" <<endl;
                break;
            }
            else{
                put_box(tmp_b);
            }

        }

        // for(int i=0;i<n;i++){
        //     for(int j=0; j<n;j++){
        //         cout << setw(2) << adj[i][j];
        //     }
        //     cout << "\n";
        // }
        sort(boxes.begin(), boxes.end(), cmp_floor);

        for(Box& tmp_b : boxes){
            if(tmp_b.is_remove) continue;
            remove_box(tmp_b);
            pair<int,int> tmp_pair = move_box(tmp_b.h, tmp_b.w, tmp_b.r, tmp_b.c, 0);
            tmp_b.r = tmp_pair.first;
            tmp_b.c = tmp_pair.second;
            put_box(tmp_b);
        }

        sort(boxes.begin(), boxes.end(), cmp_k);
    }
    return 0;
}


/*

r1,c1은 왼쪽위 꼭짓점, r2,c2는 오른쪽 아래 꼭짓점 (1)

putbox : adj맵에 box객체 넣기 
canput(5개인자) : r1,r2,c1,c2 저장후
    직사각형을 (1) 개념 참고 왼쪽 변 아래 변 오른쪽 변으로 r이나 c를 조작
        반복문, 오버플로우랑 0이 아니면 함수 폴스 반환
    트루 반환

movebox : r,c 복사후 바로 while nr, nc 만들어서 
    canput에 (h,w,nr,nc, d) 트루되면 rr과 cc 업데이트 아니면 브레이
    리턴 rr cc

main :
입력 M만큼 입력 인자들 받기
기본 r0과 c0만 저장후 
auto [r,c] =  moveBox에 넣기 (h,w,r,c,0) /아래
받은 rc로 Box b{k,h,w, ... 이런식으로 초기화};
boxes 벡터에 넣기
putbox(vector의 back 함수로 마지막에 넣은거 맵에 등록)

정렬 (번호 기준)

갯수만큼 반복
    turn %2 ==0이면 is left 부울 트루

    1. 왼쪽이나 오른쪽 빼기
    boxes 들 마다 반복 
    제거된거면 컨티뉴
    일단 removebox로 제거먼저
    auto [rr,cc] = movebox(b.h,b.w,b.r,b.c, isLeft? 1: 2) left면 1 오른쪽이면 2로 
    bool canexit = isLeft ? (cc 가 0이면) : (cc + 넓이 더한게 n이면) 부울 정의
    canexit 트루면 출력하고 브레이크
    아니면 pubbox(b)로 제거햇던거 회복

    정렬 - 바닥이 제일 높은거 기준으로 정렬

    2. 중력 적용
    for (box마다 반복)
    제거됏으면 컨티뉴
    removebox 적용
    auto nr nc = moveBox(거시기들 0)
    br = nr, bc=nc
    putbox

    k 번호 기준으로 다시 정렬

*/
