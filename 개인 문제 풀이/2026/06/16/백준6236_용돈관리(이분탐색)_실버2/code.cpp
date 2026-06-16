#include <bits/stdc++.h>
using namespace std;
#define INF 987654321
typedef long long ll;
ll n,m;
int a[100001];
int ret = INF;

bool checker(int mid){
    int idx = 1;
    int now = mid; //처음 한번 빼기
    
    for(int d=0; d<n; d++){
        if(now < a[d]){
            idx++;
            now = mid;
        }
        now -= a[d];
    }
    return (idx <= m);
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
        if(checker(mid)){
            ret = min(ret, mid);
            rightt = mid - 1;
            continue;
        }
        else{
            leftt = mid + 1;
        }
    }
    cout << ret;
    return 0;
}
