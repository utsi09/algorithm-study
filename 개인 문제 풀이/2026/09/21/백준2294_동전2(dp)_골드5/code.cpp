#include <bits/stdc++.h>
using namespace std;
int n, k;
int coin[104];

int dp[10004];

int solve(int now){
    if(now == k){
        return 0;
    }
    if(now > k){
        return 10000;
    }
    int& here = dp[now];
    if(here != -1) return here;
    here = 10000;
    for(int c : coin){
        here = min(here, solve(now + c) + 1);
    }
    return here;
}

int main(){
    cin >> n >> k;
    for(int i=0; i<n; i++){
        cin >> coin[i];
    }

    memset(dp, -1, sizeof(dp));
    int cnt = solve(0);
    if(cnt == 10000) cout << "-1";
    else cout << solve(0);

    return 0;
}
