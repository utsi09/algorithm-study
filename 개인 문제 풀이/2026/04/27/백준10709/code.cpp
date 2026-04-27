#include <bits/stdc++.h>
using namespace std;
int n,m;
const int m_size = 101;
int adj[m_size][m_size];
string s;

void debug_map(){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cout << adj[i][j]<<" ";
        }
        cout <<"\n";
    }
}

void move_cloud(int i, int j){
    int nx=j;
    int turn=0;
    while(1){
        turn++;
        nx++;
        if(nx >= m) break; //맵초과시 끝
        //cout << "move" << endl;
        if(adj[i][nx]==0) continue; //구름은 변화없음
        if(turn < adj[i][nx] || adj[i][nx] == -1){
            adj[i][nx] = turn; //최소값 갱신
        }
    }

    return;
}

int main(){
    cin >> n >> m;
    for(int i=0; i<n; i++){
        cin >> s;
        for(int j=0; j<m; j++){
            if(s[j]=='c') adj[i][j] = 0;
            else adj[i][j] = -1;
        }
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(adj[i][j] == 0) move_cloud(i,j); 
        }
    }

    debug_map();
    return 0;
}
