#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000004
int n;
int dp[MAXN];


void go(int n){
	if(n == 0) return;
	cout << n << " ";
	if(n % 3 == 0 && dp[n] - 1 == dp[n/3]) go(n/3);
	else if(n % 2 == 0 && dp[n]-1 == dp[n/2]) go(n/2);
	else if(dp[n]-1 == dp[n-1]) go(n-1);
	return;
}


int solve(int n){
    dp[1] = 0;

    for(int i = 2; i <= n; i++){
        dp[i] = dp[i-1] + 1;

        if(i % 3 == 0)
            dp[i] = min(dp[i], dp[i/3] + 1);

        if(i % 2 == 0)
            dp[i] = min(dp[i], dp[i/2] + 1);
    }

    return dp[n];
}


int main(){
	cin >> n;
	fill(&dp[0], &dp[0]+MAXN, MAXN);
	
	int tmp = solve(n);
	cout << dp[n] << endl;
	go(n);
}
