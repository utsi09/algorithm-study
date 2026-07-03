#include <bits/stdc++.h>
using namespace std;
map<int,int> _m;



int main(){
  int n,m;
  cin >> n >> m;
  for(int i=0; i<n; i++){
    int tmp; cin >> tmp;
    _m[tmp]++;
  }
  for(int i=0; i<m; i++){
    int tmp; cin >> tmp;
    _m[tmp]++;
  }
  int cnt=0;
  for(auto a : _m){
    if(a.second == 1) cnt++;
  }
  cout << cnt;
  return 0;
}
