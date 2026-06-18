#include <bits/stdc++.h>
using namespace std;
int t, n , m;
vector<int> a;
vector<int> b;
int here;
int cnt=0;

int main() {
    cin >> t;
    while(t--){
        cnt = 0;
        a.clear();
        b.clear();

        cin >> n >> m;
        for(int i=0; i<n; i++){
            int tmp; cin >> tmp;
            a.push_back(tmp);
        }
        for(int j=0; j<m; j++){
            int tmp; cin >> tmp;
            b.push_back(tmp);
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        for(int i=0; i<n; i++){
            here = a[i];
            auto pos = lower_bound(b.begin(), b.end(), here);
            cnt += (int)(pos-b.begin());
        }
        cout << cnt << '\n';
    }
    return 0;
}
