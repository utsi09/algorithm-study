#include <bits/stdc++.h>
using namespace std;
int n,m;
int adj[10][10];
int cb_n;

vector<pair<int,int>> candidates; //벽 후보지
vector<pair<int,int>> new_block; //새로운 벽
vector<pair<int,int>> viruses;
int cnt;
int visited[10][10];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0,1,0,-1};
int visited_cnt;
int init_empty;
int best_int = 0;

void dfs(int r, int c){
    visited_cnt++;
    visited[r][c] = 1;
    for(int d=0; d<4; d++){
        int ny = r + dy[d];
        int nx = c + dx[d];
        if(ny<0 || nx<0 || ny>=n || nx>=m) continue; //오버플로우
        //if(adj[ny][nx] == 2) continue; //같은 바이러스
        if(adj[ny][nx] == 1) continue; //벽
        if(visited[ny][nx]) continue;
        bool checker = false;
        for(int i=0; i<3; i++){ //새로 친 벽
            if(new_block[i].first == ny && new_block[i].second == nx){
                checker = true;
                break;
            }
        }
        if(checker) continue;
        
        dfs(ny,nx);
    }
    return;
}

void combi(int start){
    if(new_block.size() == 3){
        visited_cnt = 0;
        fill(&visited[0][0], &visited[0][0]+10*10, 0);
        for(pair<int,int> v : viruses){ 
            int r = v.first; int c = v.second;
            if(visited[r][c]) continue;
            //visited[r][c] = 1;
            dfs(r,c);
        }
        //cout << init_empty <<"," << visited_cnt << endl;
        int ans = init_empty - visited_cnt - 3 + viruses.size(); //초기 안전 영역 수 - 퍼진 수 - 새로친 벽의 수 + 바이러스 원래 수
        best_int = max(best_int, ans);
        //cout << '\n';
        return;
    }

    for(int i=start; i<cb_n; i++){
            new_block.push_back(candidates[i]);
            combi(i+1);
            new_block.pop_back();
        }
    return;
}


int main(){ 
    cin >> n >> m;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> adj[i][j];
            if(adj[i][j] == 0) {candidates.push_back({i,j}); init_empty++;}
            else if(adj[i][j] == 2) viruses.push_back({i,j});
        }
    }
    cb_n = candidates.size();
    combi(0);
    cout << best_int;
    return 0;
}
