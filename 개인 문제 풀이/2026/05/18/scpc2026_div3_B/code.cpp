#include <bits/stdc++.h>

#define PB push_back
#define MP make_pair
#define ll long long

using namespace std;

// SCPC 2026 Div.3 B

int N, M;
vector<int> w, v(5001);
vector<bool> used(5001, false);

void input(){
    cin >> N >> M;
    for(int i = 0; i<N; i++){
        int t;
        cin >> t;
        w.PB(t);
    }
    for(int i = 0; i<N-1; i++){
        int t;
        cin >> t;
        used[t] = true;
    }
}

void solve(){
    int ans = 1;
    for(int i = 1; i<=N; i++){
        if(!used[i]) ans++;
    }
    cout << ans << '\n';
}

int main(){
    input();
    solve();
    return 0;
}
