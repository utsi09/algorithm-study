#include <bits/stdc++.h>
using namespace std;
int n,d,f;
vector<pair<int,int>> v;
priority_queue<int, vector<int>, greater<int>> pq;

int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> d >> f;
        v.push_back({d,f});
    }
    sort(v.begin(), v.end());
    
    for(auto p : v){
        pq.push(p.second); //컵라면 개수 넣기
        while(pq.size() > p.first){
            pq.pop();
        }
    }
    int cnt = 0;
    while(pq.size()){
        cnt += pq.top();
        pq.pop();
    }
    cout << cnt;
    return 0;
}
