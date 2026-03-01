#include <bits/stdc++.h>
using namespace std;

int ground[100][100];
vector<int> adj[100];
int visited[100][100];
int move_lr[4] = {0, 1, 0 ,-1};
int move_ud[4] = {-1, 0, 1, 0};
int ct = 0;

void dfs(int i, int j){
    cout<< i << ":" << j << "방문" << endl;
    visited[i][j] = 1;
    for(int ctr=0; ctr<4; ctr++){
        int ni = i + move_ud[ctr];
        int nj = j + move_lr[ctr];
        if(ni<0 || ni>=100 || nj<0 || nj>=100) continue;
        if(ground[ni][nj]==0 || visited[ni][nj]==1) continue; 
        dfs(ni,nj);
    }
    
}

int main(){
    int n=0, m=0;
    cin >> n >> m;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            cin >> ground[i][j];
        }
    }


    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            if (ground[i][j]==1 && visited[i][j]!=1){
                cout<< "count 추가" <<endl;
                dfs(i,j);
                ct+=1;
            }
        }
    }
    cout << ct;
    return 0;
}
