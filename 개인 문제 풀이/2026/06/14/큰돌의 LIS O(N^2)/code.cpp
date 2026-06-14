#include <bits/stdc++.h>

using namespace std; 
int n;
int a[1004];
int cnt[1004];
int ret=0;

int main(){
    cin >> n; 
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    for(int i=0; i<n; i++){
        int max_value = 0;
        for(int j=0; j<=i; j++){
            if(max_value < a[j]){
                max_value = a[j];
                cnt[i]++;
            }
        }
        ret = max(ret, cnt[i]);
    }
    cout << ret;

    return 0;
} 
