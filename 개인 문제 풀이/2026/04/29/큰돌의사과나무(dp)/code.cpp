#include <bits/stdc++.h>
using namespace std;
int s,m;
int d[101];
int dp[101][2][31];
int cnt;


int go(int idx, int tree, int cnt){
    if(cnt < 0) return -1e9;
    if(idx == s) return 0;
    int &ret = dp[idx][tree][cnt];
    if(ret != -1) return ret;
    return max(go(idx+1,tree,cnt), go(idx+1,tree^1,cnt-1)) + (tree == d[idx] - 1);
}

int main() {
    memset(dp, -1, sizeof(dp));
    cin >> s >> m;
    for(int i=0; i<s; i++){
        cin >> d[i];
    }
    cnt = max(go(0,0,m), go(0,1,m-1));

    cout << cnt;
    return 0;
}
