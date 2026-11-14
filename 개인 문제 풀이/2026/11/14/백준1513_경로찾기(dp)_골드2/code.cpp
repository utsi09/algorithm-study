#include <bits/stdc++.h>
using namespace std;
int n,m,c;
int adj[51][51];
int tmpi, tmpj;
int dp[51][51][51][51];
int mod = 1000007;

int go(int i, int j, int cnt, int prev){
  if(i >= n || j >= m) return 0; //오버플로우

  if(i+1 == n && j+1 == m){ //기저사례
    if(cnt == 0 && adj[i][j] == 0) return 1;
    if(cnt == 1 && adj[i][j] > prev) return 1;
    return 0;
  }

  int& ret = dp[i][j][cnt][prev];
  if(ret != -1) return ret;
  ret = 0;

  if(adj[i][j] == 0){ //증가하는 오락실
    ret = (go(i+1, j, cnt, prev) + go(i, j+1, cnt, prev)) % mod; 
  }
  else if(adj[i][j] > prev){ //그 외(감소하는 오락실 포함)
    ret = (go(i+1, j, cnt-1, adj[i][j]) + go(i, j+1, cnt-1, adj[i][j])) % mod;
  }
  return ret;
}




int main(){
  cin >> n >> m >> c;
  for(int i=1; i<=c; i++){
    cin >> tmpi >> tmpj;
    tmpi--; tmpj--;
    adj[tmpi][tmpj] = i;
  }

  for(int i=0; i<=c; i++){
    memset(dp, -1, sizeof(dp));
    cout << go(0, 0, i, 0) << " ";
  }


  return 0;
}
