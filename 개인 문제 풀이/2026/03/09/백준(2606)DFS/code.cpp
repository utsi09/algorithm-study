#include <bits/stdc++.h>
using namespace std;
int N=0;
int connect = 0;
vector<int> adj[101];
int visited[101];
int x,y;
int ret = 0;

void DFS(int i){
    visited[i] = 1;
    for (auto &next : adj[i]){
        if(visited[next]) continue;
        ret++;
        DFS(next);
    }
}

int main(){
    cin >> N;
    cin >> connect;
    for (int i=0; i<connect; i++){
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    DFS(1);
    cout << ret << endl;
    return 0;
}
