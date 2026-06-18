#include <bits/stdc++.h>
using namespace std;
int t, n , m;
int a[20001];
vector<int> b;
int leftt, rightt, mid;
int here;
int cnt=0;



bool checker(int mid){
    //cout << here << " vs " << b[mid] << '\n';
    return here > b[mid]; //실질 먹이값이랑 사냥꾼 값이랑 비교
}

int main() {
    cin >> t;
    for(int turn=0; turn<t; turn++){
        cnt = 0;
        memset(a, 0, sizeof(a));
        b.clear();

        cin >> n >> m;
        for(int i=0; i<n; i++){
            cin >> a[i];
        }
        for(int j=0; j<m; j++){
            int tmp; cin >> tmp;
            b.push_back(tmp);
        }
        sort(b.begin(), b.end());
        
        for(int i=0; i<n; i++){
            leftt = 0; 
            rightt = m - 1;
            here = a[i]; //현재 사냥꾼 A
            while(1){
                // if(rightt == -1){
                //     mid = -1;
                //     break;
                // }
                
                mid = (leftt + rightt) / 2;
                if(checker(mid)){
                    leftt = mid + 1;
                    if(leftt > rightt){
                        cnt += mid + 1;
                        break;
                    }
                }
                else {
                    rightt = mid - 1;
                    if(leftt > rightt){
                        cnt += mid;
                        break;
                    }
                    //cout << rightt << " : right\n";
                }
            }
            //cout << turn << " : turn, and " << mid+1 <<'\n';
        }
        cout << cnt << '\n';
    }
    return 0;
}
