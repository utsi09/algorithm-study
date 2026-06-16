#include <bits/stdc++.h>
using namespace std;
#define INF 987654321
int n,m;
int a[100001];
int ret = INF;

int checker(int mid){
    int idx = 1;
    int now = mid; //처음 한번 빼기
    
    for(int d=0; d<n; d++){
        if(now >= a[d]){
            now -= a[d];
        }
        else {
            idx++;
            now = mid;
            if(now >= a[d]){
                now -= a[d];
            }
            else return 2; //풀피인데 안되면 안되는거지
        }
    }
    if(idx == m) return 0;
    else if(idx < m) return 1;
    else if(idx > m) return 2;
}

int main() {
    cin >> n >> m;
    int leftt=1; int rightt=0;
    for(int i=0; i<n; i++){
        cin >> a[i];
        rightt += a[i];
    }
    while(1){
        if(leftt > rightt) break;
        int mid = (leftt + rightt) / 2;
        int tmp = checker(mid);
        if(tmp == 0){
            ret = min(ret, mid);
            rightt = mid - 1;
            continue;
        }
        else if(tmp == 1){
            rightt = mid - 1;
            continue;
        }
        else if(tmp == 2){
            leftt = mid + 1;
            continue;
        }
    }
    cout << ret;
    return 0;
}
