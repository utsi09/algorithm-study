#include <iostream>
#include <stack>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int n;
vector<pair<int,int>> tc;
priority_queue<int,vector<int>,greater<int>> pq;
int ret=0;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    for(int i=0; i<n; i++){
        int d; int c; cin >> d>> c;
        tc.push_back({d,c});
    }
    sort(tc.begin(),tc.end());

    for(int i=0; i<n; i++){
        pq.push(tc[i].second);
        if(pq.size() > tc[i].first){
            pq.pop();
        }
    }
    while(pq.size()){
        ret += pq.top(); pq.pop();
    }
    cout << ret;
    return 0;
}

