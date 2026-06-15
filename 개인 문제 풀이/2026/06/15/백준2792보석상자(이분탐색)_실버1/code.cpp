#include <bits/stdc++.h>
using namespace std;
#define INF 987654321
int n,m;
int a[300001]; //색상의 개수
int leftt=1;
int rightt=0;
int ret = INF;


bool binary_search(int mid){
    int ret = 0;
    for(int i=0; i<m; i++){
        ret += a[i] / mid;
        if(a[i] % mid) ret++;
    }
    return ret <= n;
}

int main() {
    cin >> n >> m;
    for(int i=0; i<m; i++){
        cin >> a[i];
        rightt = max(rightt, a[i]);
    }   
    while(1){
        int mid = (leftt + rightt) / 2; 
        if(leftt > rightt) break;
        else if(binary_search(mid)){
            ret = min(ret, mid);
            rightt = mid - 1; //더 작은 ret 탐색
        }
        else{
            leftt = mid + 1; // 더 관대한 ret 탐색
        }

    }
    cout << ret;
    return 0;
}
