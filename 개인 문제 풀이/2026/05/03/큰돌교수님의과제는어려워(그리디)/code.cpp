#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,k;
int ret=0;


int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
    cin >> n;
    priority_queue<float> pq;
    for(int i=0; i<n; i++){
        float tmp; cin >> tmp;
        pq.push(tmp);
        if(pq.size() <= 5){
            continue;
        }
        else{
            pq.pop();
        }
    }
    vector<float> ret;
    int q_size = pq.size();
    while(pq.size()){
        ret.push_back(pq.top()); pq.pop();
    }
    for(int i=q_size-1; i>=0; i--){
        cout << ret[i] << "\n";
    }
    return 0;
}

