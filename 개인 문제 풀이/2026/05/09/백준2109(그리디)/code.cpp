#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int n;
vector<pair<int,int>> v;
priority_queue<int, vector<int>, greater<int>> pq;
int ret =0;

int main() {
    cin >> n;
    for(int i=0; i<n; i++){
        int p; int d; cin >> p >> d;
        v.push_back({d,p});
    }
    sort(v.begin(), v.end());
    for(int i=0; i<n; i++){
        pq.push(v[i].second);
        if(pq.size() > v[i].first) pq.pop();
    }
    while(pq.size()){
        ret += pq.top(); pq.pop();
    }
    cout << ret;

    return 0;
}
