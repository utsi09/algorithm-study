#include <bits/stdc++.h>

using namespace std;
const int map_size = 101;
int adj[map_size][map_size];
int visited[map_size][map_size];
int max_ground = 0;
vector<int> ground_size;
int n=0,m=0;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int cnt = 0;
int ret = 0;
void DFS(int i, int j){
    visited[i][j] = 1;
    for(int k=0; k<4; k++){
        int ny = i + dy[k];
        int nx = j + dx[k];
        if(ny<0 || ny>=n || nx<0 || nx>=m) continue;
        if(adj[ny][nx]) continue;
        if(visited[ny][nx]) continue;
        cnt++;
        DFS(ny,nx);
    }
    
}

int main() {
    int k=0;
    int sx=0, sy=0;
    int ex=0, ey=0;
    cin >> n >> m >> k;
    for (int i=0; i<k; i++){
        cin >> sx >> sy >> ex >> ey;
        for (int j=sy; j<ey; j++){
            for (int l=sx; l<ex; l++){
                adj[j][l] = 1;
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cnt=0;
            if(visited[i][j] || adj[i][j]) continue;
            cnt++; ret++;
            DFS(i,j);
            ground_size.push_back(cnt);
        }
    }

    sort(ground_size.begin(), ground_size.end());
    
    cout << ret << endl;
    for(int i : ground_size){
        cout <<i<<" ";
    }

}
