#include <bits/stdc++.h>
using namespace std;
int n;
int now = 0;



int main(){
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    cin >> n;
    for(int i=0; i<n; i++){
        int t, w;
        cin >> t >> w;
        pq.push({t,w});
    }
    for(int i=0; i<n; i++){
        int t, w;
        t = pq.top().first;
        w = pq.top().second;
        pq.pop();
        now = max(t, now);
        now += w;
    }
    cout << now;
    return 0;
}
