#include <bits/stdc++.h>
using namespace std;
#define INF 10e8 
int n,m,s;
vector<pair<int,int>> adj[20004]; //u - [w, v] 
vector<int> dist(20004, INF);
int now_v, now_w;

void dijkstra(int start){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    dist[start] = 0;
    pq.push({0, start}); //출발지 자기자신 거리는 0
    while(pq.size()){
        tie(now_w, now_v) = pq.top();
        pq.pop();
        if(dist[now_v] != now_w) continue;
        for(pair<int,int> p : adj[now_v]){
            int n_w = p.first;
            int n_v = p.second;
            int new_cost = now_w + n_w;
            if(dist[n_v] > new_cost){
                cout << "dist to " << n_v << "is renew to "<< new_cost <<'\n';
                dist[n_v] = new_cost;
                pq.push({new_cost, n_v});
            }
        }
    }
    return;
}

int main() {
    cin >> n >> m >> s;
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({w,v});
    }
    dijkstra(s);

    for(int i=1; i<=n; i++){
        if(dist[i] == INF) cout << "INF \n";
        else cout << dist[i] <<'\n';
    }
    return 0;
}
