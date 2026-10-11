#include <bits/stdc++.h>
using namespace std;

int dp[10000]; //현재 소비한 돈 : 최대 칼로리
double raw_money = 0;
int money, n;

vector<pair<int,int>> candies(5001);


int hacking(int m){
    int& here = dp[m];
    if(here != -1) return here;
    here = 0;
    for(int i=0; i<n; i++){
        if(m + candies[i].second > money) continue;
        here = max(here, hacking(m + candies[i].second) + candies[i].first); // dp
    }
    return here;
}

int main(){

    while(1){
        candies.resize(5001);
        cin >> n;
        cin >> raw_money;
        money = int(round(raw_money * 100));
        if(n == 0 && money == 0) break;
        
        for(int i=0; i<n; i++){
            cin >> candies[i].first;
            cin >> raw_money;
            candies[i].second = int(round(raw_money * 100));
        }
        memset(dp, -1, sizeof(dp));
        cout << hacking(0) <<'\n';
        candies.erase(candies.begin(), candies.end());
    }

    return 0;
}
