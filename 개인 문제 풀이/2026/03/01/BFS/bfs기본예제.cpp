#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100];
int visited[100];

void BFS(int i){
    visited[i] = 1;
    queue<int> q;
    q.push(i);
    while(q.size()){
        int here = q.front();
        q.pop();
        for(int& there : adj[here]){
            if(visited[there]) continue;
            q.push(there);
            visited[there] = visited[here] + 1;
        }
    }
}

int main(){
    adj[10].push_back(12);
    adj[10].push_back(14);
    adj[10].push_back(16);
    adj[12].push_back(18);
    adj[12].push_back(20);
    adj[20].push_back(22);
    adj[20].push_back(24);
    BFS(10);
    cout << visited[24] -1 << endl;
    return 0;
}
