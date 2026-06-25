#include <bits/stdc++.h>
using namespace std;
#define INF 1e9
int n,m;
int dis[104][104];

int main() {
    cin >> n >> m;
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(i==j) dis[i][j] = 0;
            else dis[i][j] = INF;
        }
    }
    
    for(int i=0; i<m; i++){
        int u,v,w;
        cin >> u >> v >> w;
        dis[u][v] = min(dis[u][v], w);
    }

    for(int k=1; k<=n; k++){
        for(int i=1; i<=n; i++){
            for(int j=1; j<=n; j++){
                dis[i][j] = min(dis[i][k] + dis[k][j], dis[i][j]);
            }
        }
    }

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(dis[i][j] == INF){
                cout << "
                INF ";
                continue;
            }
            cout << dis[i][j] <<" ";
        }
        cout <<'\n';
    }

    return 0;
}

/*
4 4
1 2 4
1 3 1
3 2 2
2 4 1

0 3 1 4
INF 0 INF 1
INF 2 0 3
INF INF INF 0
*/
