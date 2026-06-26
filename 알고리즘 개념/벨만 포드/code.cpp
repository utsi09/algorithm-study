#include<bits/stdc++.h>
using namespace std;
#define INF 1e9
int n,m;
vector<pair<int,int>> adj[1004];
vector<int> dist(1004, INF);


int main(){
    cin >> n >> m;
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({w,v});
    }
    dist[1] = 0; 
    queue<int> q;
    for(int i=0; i<n; i++){
        for(int here = 1; here <= n; here++){
            for(pair<int,int> arrow : adj[here]){
                int weight = arrow.first;
                int to = arrow.second;
                int new_cost = weight + dist[here];
                if(dist[here] != INF && dist[to] > new_cost){
                    if(i == n-1) q.push(to);
                    dist[to] = new_cost;
                }
            }
        }
    }
    if(q.size()) {cout<< "-1"; return 0;}
    for(int i=1; i<=n; i++){
        cout << dist[i] << '\n';
    }
}
