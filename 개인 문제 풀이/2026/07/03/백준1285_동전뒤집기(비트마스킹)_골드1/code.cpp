#include <bits/stdc++.h>
using namespace std;
int n;
int adj[21];
int ret = 98765432;

//  1 << (n-1)  = 100, 
void solve(int here, int v[21]){
    //cout << "hi" << '\n';
    if(here == n){
        int cnt=0;
        for(int j = 1<<(n-1); j>0; j/=2){ // 0 열부터 검사
            int tmp=0;
            for(int i=0; i<n; i++){
                if(v[i] & j) tmp++;
            }
            tmp = min(tmp, n-tmp);
            //cout << tmp << "vs" << n-tmp << " = " << tmp <<'\n';
            cnt += tmp;
        }
        ret = min(ret, cnt);
        return;
    }

    solve(here+1, v);
    v[here] = ~v[here];
    solve(here+1, v);
    return;
}


int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        string s;
        cin >> s;
        int num = 1;
        for(int j=n-1; j>=0; j--){
            if(s[j] == 'T'){
                adj[i] |= num;
            }
            num *= 2;
        }
    }
    
    solve(0, adj);
    cout << ret;
    return 0;
}
