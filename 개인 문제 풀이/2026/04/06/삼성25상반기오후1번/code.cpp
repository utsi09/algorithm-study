#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <queue>
#include <set>

using namespace std;
int n, q;
int bfs_cnt = 0;

struct Virus{
    int min_i, min_j, k;
    vector<pair<int,int>> shape;
    bool is_die=false;
};

vector<Virus> viruses;
int adj[16][16];
int visited[16][16];
int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};


void put_virus(Virus& v){
    int i = v.min_i;
    int j = v.min_j;

    for(pair<int,int>& v1 : v.shape){
        adj[i+v1.first][j+v1.second] = v.k;
    }
}

void remove(Virus& v){
    int i = v.min_i;
    int j = v.min_j;

    for(pair<int,int>& v1 : v.shape){
        if(adj[i+v1.first][j+v1.second] == v.k) adj[i+v1.first][j+v1.second] = 0;
    }
}

void check_edit(Virus& v){
    int i = v.min_i;
    int j = v.min_j;
    vector<pair<int,int>> new_shape;
    for(pair<int,int>& v1 : v.shape){
        if(adj[i+v1.first][j+v1.second] == v.k){
            new_shape.push_back({v1.first,v1.second});
        }
    }
    v.shape = new_shape;
}

void BFS(int i, int j, int k){
    visited[i][j] = 1;
    queue<pair<int,int>> q;
    q.push({i,j});
    while(q.size()){
        int n_i = q.front().first;
        int n_j = q.front().second;
        q.pop();
        for(int d=0;d<4;d++){
            int ny = n_i + dy[d];
            int nx = n_j + dx[d];
            if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
            if(adj[ny][nx] != k) continue;
            if(visited[ny][nx] != 0) continue;
            visited[ny][nx] = 1;
            q.push({ny,nx});
            bfs_cnt++;
        }
    }
}

bool size_cmp(Virus& v1, Virus& v2){ 
    if(v1.shape.size() == v2.shape.size()){
        return v1.k < v2.k;
    }
    if(v1.shape.size() > v2.shape.size()) return true;
    return false;
}

bool k_cmp(Virus& v1, Virus& v2){
    if(v1.k < v2.k) return true;
    return false;
}

int main(){
    cin >> n >> q;
    for(int k=1; k<=q; k++){
        int c1,r1,c2,r2; cin >> c1 >> r1 >> c2 >> r2;
        //투입
        //바이러스 객체 만들기
        Virus v;
        v.min_i=r1; v.min_j=c1; v.k = k;
        for(int i=r1; i<r2; i++){
            for(int j=c1; j<c2; j++){
                v.shape.push_back({i-v.min_i, j-v.min_j}); //상대좌표
            }
        }
        viruses.push_back(v);
        put_virus(v);
        
        //cout << v.min_i << ": mini" << v.min_j << " minj" <<endl;

        //겹치면 잡아먹기
        for(Virus& tmp_v : viruses){
            check_edit(tmp_v); //다시 쉐이프들 갱신
        }

        for(Virus& tmp_v : viruses){
            int min_i = 987654;
            int min_j = 987654;
            for(pair<int,int> p : tmp_v.shape){
                min_i = min(min_i, p.first);
                min_j = min(min_j, p.second);
            }
            tmp_v.min_i += min_i; 
            tmp_v.min_j += min_j;
            for(pair<int,int>& p : tmp_v.shape){ //상대좌표들 min 기준 업데이트
                p.first -= min_i;
                p.second -= min_j;
            }

            if(tmp_v.shape.empty()) {
                tmp_v.is_die = true;
                continue;
            }
            int start_i = tmp_v.min_i + tmp_v.shape[0].first;
            int start_j = tmp_v.min_j + tmp_v.shape[0].second;

            fill(&visited[0][0], &visited[0][0] + 16*16, 0);
            bfs_cnt = 1;
            BFS(start_i, start_j, tmp_v.k);
            if(bfs_cnt != tmp_v.shape.size()){
                tmp_v.is_die = true;
                remove(tmp_v);
            }
            
        }
        //  for(int i=n-1;i>=0;i--){
        //     for(int j=0;j<n;j++){
        //         cout << setw(1) << adj[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        // for(int i=n-1;i>=0;i--){
        //     for(int j=0;j<n;j++){
        //         cout << setw(1) << adj[i][j] << " ";
        //     }
        //     cout << endl;
        // }

        //크기순으로 이동
        fill(&adj[0][0], &adj[0][0] + 16*16, 0); //맵 초기화

        sort(viruses.begin(), viruses.end(), size_cmp);

        for(Virus& v : viruses){
            if(v.is_die) continue;
            bool placed = false;
            for(int j=0; j<n; j++){
                for(int i=0; i<n; i++){
                    bool can_move=1;
                    for(pair<int,int> node : v.shape){ //노드 한개씩 이동
                        int ny = node.first + i;
                        int nx = node.second + j;
                        if(ny<0 || nx<0 || ny>=n || nx>=n || adj[ny][nx] != 0) { //0이 아니거나 오버플로우
                            can_move=0;
                            break;
                        }
                    }
                    if(can_move){
                        v.min_i = i;
                        v.min_j = j;
                        placed = true;
                        break;
                    }
                }
                if(placed) break;
            }
            if(!placed) v.is_die = true;
            else put_virus(v);
        }

        


        //인접무리 set
        vector<pair<int,int>> adj_virus;

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                for(int d=0; d<4; d++){
                    int ny = i + dy[d];
                    int nx = j + dx[d];
                    if(ny<0 || nx<0 || ny>=n || nx>=n) continue;
                    if(adj[i][j] == 0 || adj[ny][nx] == 0) continue;
                    if(adj[i][j] != adj[ny][nx]){
                        int k1 = adj[i][j];
                        int k2 = adj[ny][nx];
                        if(k1 > k2) swap(k1,k2);
                        adj_virus.push_back({k1, k2});
                    }
                }
            }
        }
        sort(adj_virus.begin(), adj_virus.end());
        adj_virus.erase(unique(adj_virus.begin(), adj_virus.end()), adj_virus.end());

        //크기 출력
        sort(viruses.begin(), viruses.end(), k_cmp);

        long long cnt = 0;
        for(pair<int,int> pos : adj_virus){
            int k1 = pos.first;
            int k2 = pos.second;
            cnt += (long long) viruses[k1-1].shape.size() * viruses[k2-1].shape.size();
        }
        cout << cnt << endl;

    }

    return 0;
}

/*
구조체 min_x, min_y, vector<pair<int,int>> shape; is_die, 

set, 

sort, erase(unique(),end) 로 중복 제거


*/
