#include <bits/stdc++.h>
using namespace std;

int T =0;
int n=0, m=0, num=0;
int start_x=0, start_y=0;
int end_x=0, end_y=0;

const int map_size = 51;
int adj[map_size][map_size];
int visited[map_size][map_size];

int dx[4] = {0,1,0,-1};
int dy[4] = {1,0,-1,0};

void DFS(int y, int x){
    visited[y][x] = 1;
    for(int i=0; i<4; i++){
        int there_y = y + dy[i];
        int there_x = x + dx[i];
        if(there_y<0 || there_y>=n || there_x<0 || there_x>=m || adj[there_y][there_x] == 0) continue;
        if(visited[there_y][there_x] == 1) continue;
        DFS(there_y, there_x);
    }
}

int main(){
    cin >> T;
    for(int i=0; i<T; i++){
        int cnt = 0;
        fill(&adj[0][0], &adj[0][0]+51*51, 0);
        fill(&visited[0][0], &visited[0][0]+51*51, 0);

        cin >> n >> m >> num;
        for(int k=0; k<num; k++){
            int i=0, j=0;
            cin >> i >> j;
            adj[i][j] = 1;
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(adj[i][j] == 0 || visited[i][j] == 1) continue;
                DFS(i,j);
                cnt++;
            }
        }

        cout << cnt << endl;
    }

    
    return 0;
}
