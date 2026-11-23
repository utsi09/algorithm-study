#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int t;
int n,m;
vector<int> adj[1004];
int visited[1004];


/*
트리는 dfs 한번으로 모두 순회 가능 = 연결
트리는 노드 = 간선 + 1 
*/


void dfs(int i){
    visited[i] = 1;
    //cout << i << " : visited \n";
    for(int next : adj[i]){
        if(next == 0) continue;
        //cout << "check : " << next <<'\n';
        if(!visited[next]){
            dfs(next);
        }
    }
    return;
}

int main(){
    cin >> t;
    while(t--){
        cin >> n >> m;
        memset(visited, 0, sizeof(visited));
        memset(adj, 0, sizeof(adj));
        int cnt = 0;
        for(int i=0; i<m; i++){
            int a,b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        for(int p=1; p<=n; p++){
            if(visited[p]) continue;
            //cout << p << " start circle \n";
            dfs(p);
            cnt++;
        }
        if(cnt == 1 && n == m + 1){
            cout << "tree\n";
        }
        else cout << "graph\n";
    
    }



    return 0;
}