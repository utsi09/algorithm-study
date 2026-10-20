#include <bits/stdc++.h>
using namespace std;
int n,k;
int w,v;
vector<pair<int,int>> item;

int dp[101][100004]; //현재idx, 현재 배낭무게

int solve(int idx, int bag){
    int& here = dp[idx][bag];
    if(here != -1) return here;
    here = 0;
    for(int i=idx; i<n; i++){
        if(bag + item[i].first > k) continue; //무게 초과
        here = max(here, solve(i+1, bag + item[i].first) + item[i].second);

        here = max(here, solve(i+1, bag));
    }
    return here;
}



int main(){
  cin >> n >> k;
  for(int i=0; i<n; i++){
    cin >> w >> v;
    item.push_back({w,v});
  }

  memset(dp, -1, sizeof(dp));
  cout << solve(0,0);


  return 0;
}
