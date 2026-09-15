#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


ll dp[31][31], n;

ll solve(int whole, int half){

    if(whole == 0 && half == 0) return 1;
    ll& here = dp[whole][half];
    if(here != -1) return here;
    here = 0;
    if(whole > 0) here += solve(whole-1, half+1);
    if(half > 0) here += solve(whole, half-1);
    return here;
}


int main(){

    memset(dp, -1, sizeof(dp));

    while(1){
        cin >> n;
        if(n == 0) break;
        cout << solve(n, 0) << '\n';
    }



}
