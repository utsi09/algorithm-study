#include <string>
#include <vector>
#include <iostream>

using namespace std;
int adj[1004][1004];
int dy[3] = {1, 0, -1}; //아래 오른 왼대각
int dx[3] = {0, 1, -1};
int t_size = 0;
int ii = 0;
int jj = 0;


vector<int> solution(int n) {
    vector<int> answer;
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=i; j++){
            t_size++;
        }
    }
    int cnt = 1;
    int nd = 0;
    for(int i=t_size; i>0; i--){
        adj[ii][jj] = cnt;
        if(cnt == t_size) break;
        cnt++;
        int ny = 0;
        int nx = 0;
        while(1){
            ny = ii + dy[nd];
            nx = jj + dx[nd];
            if(adj[ny][nx] != 0 || ny >= n || 
               nx >= n || ny <0 || nx<0){ //
                nd = (nd+1) % 3;
            }
            else break;
        }
        ii = ny;
        jj = nx;
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<=i; j++){
            answer.push_back(adj[i][j]);
        }
    }
        
    return answer;
}