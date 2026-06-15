#include <bits/stdc++.h>
using namespace std; 
int n;
int a[1004];
int cnt[1004];
int prev_i[1004];
int ret=0;
int idx;

void go(int idx){
    cout << a[idx] << " ";
    if(prev_i[idx] == -1) return;
    go(prev_i[idx]);
    return;
}


int main(){
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> a[i];
    }
    fill(&cnt[0], &cnt[0]+1004, 1);
    fill(&prev_i[0], &prev_i[0]+1004, -1);
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            if(a[j] < a[i] && cnt[j]+1 > cnt[i]){
                cnt[i] = cnt[j]+1;
                prev_i[i] = j;
            }
        }
        if(ret < cnt[i]){
            ret = cnt[i];
            idx=i;
        }
    }
    //cout << ret;
    go(idx);
    return 0;
} 
