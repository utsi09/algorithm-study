#include <bits/stdc++.h>
using namespace std;
int N = 0;
vector<int> v;
int ret;

void go(int idx, int sum){
    if(idx == N){
        ret = max(ret, sum % 11);
        // cout << ret << endl;
        return;
    }
    go(idx+1, sum + v[idx]); go(idx+1, sum);
}

int main() {
    cin >> N;
    for(int i=0; i<N; i++) {
        int tmp;
        cin >> tmp;
        v.push_back(tmp);
    }
    go(0,0);
    cout << ret << endl;
    return 0;
}
