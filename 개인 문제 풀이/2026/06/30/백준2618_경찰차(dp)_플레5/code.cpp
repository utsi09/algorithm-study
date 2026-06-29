#include <bits/stdc++.h>
using namespace std; 
#define INF 98765432
int py[1004];
int px[1004];
int n,w;
int dp[1004][1004];

int d(int police, int accident){
    int i = py[police];
    int j = px[police];
    int ii = py[accident];
    int jj = px[accident];
    return (abs(i-ii) + abs(j-jj));
}

int get_sum(int a, int b){
    int goal = max(a,b) + 1;
    if(goal > w+1) return 0; // w=2, next = 4 , (2,3) 첫트 골 - 2 , 2 > 3 ㄴ, 2트 골 - 3 , 3 > 3 ㄴ, 3트 골 4
    int& here = dp[a][b];
    if(here != -1) return here;
    here = INF;
    return here = min(get_sum(goal, b) + d(a, goal), get_sum(a, goal) + d(b, goal));
}

void solve(){
    int i=0; int j=1;
    for(int t=2; t<=w+1; t++){ // 첫트 2, 2<=3 ㅇㅋ 2트 3, 3<=3 ㅇㅋ
        if(dp[t][j] + d(i,t) < dp[i][t] + d(j,t)){
            puts("1");
            i = t;
        }
        else{
            puts("2");
            j = t;
        }
    }
}

int main(){   
    cin >> n >> w;
    py[0] = 1; px[0] = 1;
    py[1] = n; px[1] = n;
    for(int i=2; i<w+2; i++){
        cin >> py[i] >> px[i];
    }
    memset(dp, -1, sizeof(dp));
    cout << get_sum(0,1) <<'\n';
    solve();
    return 0;
}
