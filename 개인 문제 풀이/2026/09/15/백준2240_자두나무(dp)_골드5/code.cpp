#include <bits/stdc++.h>
using namespace std;
int t, w;
int m[1001];
int dp[1001][2][31];



int solve(int idx, int tree, int chance){
    if(chance < 0) return -1e9;
    if(idx == t) return 0;
    int& here = dp[idx][tree][chance];

    if(~here) return here;
    here = 0;

    here = max(solve(idx+1, tree, chance), solve(idx+1, tree^1, chance-1)) + ((m[idx] - 1) == tree ? 1 : 0); 
    return here;
}

int main(){
    cin >> t >> w;
    for(int i=0; i<t; i++){
        cin >> m[i];
    }

    memset(dp, -1, sizeof(dp));
    cout << max(solve(0,0,w), solve(0,1,w-1));




    return 0;
}
