#include <bits/stdc++.h>
using namespace std;
int n;
vector<pair<int,int>> v;
priority_queue<int, vector<int>, greater<int>> pq;
int ret = 0;

int main(){
  cin >> n;
  for(int i=0; i<n; i++){
    pair<int,int> tmp;
    cin >> tmp.first >> tmp.second;
    v.push_back(tmp);
  }
  sort(v.begin(), v.end());

  for(int i=0; i<n; i++){
    ret += v[i].second;
    pq.push(v[i].second);
    if(pq.size() > v[i].first){ //
      ret -= pq.top();
      pq.pop();
    }
  }
  cout << ret;

  return 0;
}
